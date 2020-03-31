// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

#include "GameCore/Enemy.h"
#include "Core/Bullet.h"
#include "Core/TurretBuff.h"
#include "Core/AttackBehavior.h"

#define LOCTEXT_NAMESPACE "Turret"

ATurret::ATurret(const FObjectInitializer& ObjectInitializer) : ALunePawnBase(ObjectInitializer), RangeMul(1.f), Range(50), AgilityOffset(0), AgilityMul(1.f), Agility(200), AttackPointPercentage(0.3f), AttackFired(false)
{
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	RootComponent = AttackRange;
	AttackRange->InitSphereRadius(Range);
	AttackRange->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnAttackRangeBeginOverlap);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnAttackRangeEndOverlap);
	AttackRange->SetGenerateOverlapEvents(true);
	bGenerateOverlapEventsDuringLevelStreaming = 1;
	static ConstructorHelpers::FClassFinder<ABullet> BulletVisual(TEXT("Blueprint'/Game/CoreObjects/BulletBp.BulletBp_C'"));
	BulletPrototype = BulletVisual.Class;

	TurretName = LOCTEXT("TurretName_GeneralClass", "Turret");
	DisplayTurretName_FT = LOCTEXT("DisplayTurretName_FT", "{0} - Lv {1}");
	DisplayDamage = LOCTEXT("DisplayDamage", "Damage");
	DisplayAgility = LOCTEXT("DisplayAgility", "Agility");
	DisplayRange = LOCTEXT("DisplayRange", "Range");
}


void ATurret::BeginPlay()
{
	Super::BeginPlay();
	RecalculateRange();
	RecalculateAgility();
	SetupRange();
}

void ATurret::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (AimingTarget) {
		TickAttack(DeltaTime);
	}
}

void ATurret::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	AttackRange->OnComponentBeginOverlap.RemoveDynamic(this, &ATurret::OnAttackRangeBeginOverlap);
	AttackRange->OnComponentEndOverlap.RemoveDynamic(this, &ATurret::OnAttackRangeEndOverlap);
}

void ATurret::ReadAttackers()
{
	for (UAttackBehavior* attacker : Attackers) {
		UE_LOG(LuneProject, Log, TEXT("Turret Attacker name: %s"), *attacker->GetUniqueName().ToString());
	}
}

void ATurret::OnAttackRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy && CanAttackEnemy(Enemy)) {
		if (!WatchList.Contains(Enemy)) {
			WatchList.Add(Enemy);
		}
		else {
			UE_LOG(LuneProject, Error, TEXT("Enemy Begin Overlap Twice"));
		}
		Enemy->OnEnemyKilled.AddDynamic(this, &ATurret::OnWatchedEnemyKilled);
		if (AimingTarget == nullptr) {
			RefreshTarget();
		}
	}
}

void ATurret::OnAttackRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy) {
		Enemy->OnEnemyKilled.RemoveDynamic(this, &ATurret::OnWatchedEnemyKilled);
		WatchList.Remove(Enemy);
		if (AimingTarget == Enemy) {
			RefreshTarget();
		}
	}
}

void ATurret::OnWatchedEnemyKilled(AEnemy* Enemy, ATurret* TurretInstigator, const EEnemyDieReason Reason) {
	WatchList.Remove(Enemy);
	if (AimingTarget == Enemy) {
		AimingTarget = nullptr;
		RefreshTarget();
	}
}

void ATurret::RefreshTarget() {
	if (WatchList.Num()) {
		AimingTarget = WatchList[0];
	}
	else
		AimingTarget = nullptr;
	AttackPhase = 0.f;
	AttackFired = false;
}

void ATurret::AddBuff(UTurretBuff* Buff) {
	if (Buff->CanApplyToTurret(this)) {
		ActiveBuffs.Add(Buff);
		Buff->BuffOwner = this;

	}
}

bool ATurret::CanAttackEnemy(AEnemy* Enemy) const {
	return GroundAirAbility & Enemy->GroundAirState;
}

ABullet* ATurret::GenerateBullet(AEnemy* Target) {
	ensureAlwaysMsgf(BulletPrototype, TEXT("BulletPrototype != 0"));
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.Instigator = this;
	auto Bullet = GetWorld()->SpawnActor<ABullet>(BulletPrototype, GetActorLocation(), GetActorRotation(), Params);
	if (!Bullet) {
		UE_LOG(LuneProject, Error, TEXT("Generate Bullet == 0"));
		return nullptr;
	}
	Bullet->SetTurretOwner(this);
	Bullet->SetTarget(Target);
	Bullet->Speed = BulletSpeed;

	for (auto TB : ActiveBuffs) {
		TB->RetrofitBullet(Bullet);
	}
	return Bullet;
}

void ATurret::TickAttack(float DeltaTime) {
	if (AimingTarget == nullptr || AimingTarget->IsPendingKill()) {
		RefreshTarget();
	}
	if (!AimingTarget) {
		return;
	}
	AttackPhase += DeltaTime;
	if (AttackPhase >= AttackPoint && !AttackFired) {
		GenerateBullet(AimingTarget);
		AttackFired = true;
	}
	if (AttackPhase >= AttackWeek) {
		AttackPhase -= AttackWeek;
		AttackFired = false;
	}
}

FText ATurret::GetUITurretName() {
	return FText::Format(DisplayTurretName_FT, TurretName, Level);
}

#undef LOCTEXT_NAMESPACE

