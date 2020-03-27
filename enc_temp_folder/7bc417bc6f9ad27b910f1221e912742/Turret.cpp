// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Engine/World.h"
#include "GameCore/Enemy.h"
#include "Core/Bullet.h"
#include "Core/TurretBuff.h"
#include "Core/AttackBehavior.h"


ATurret::ATurret(const FObjectInitializer& ObjectInitializer) : ALunePawnBase(ObjectInitializer), DamageOffset(0), DamageAddon(0), DamageMul(1.f), RangeMul(1.f), Damage(20), Range(50), BulletPrototype(ABullet::StaticClass()), AgilityOffset(0), AgilityMul(1.f), Agility(200), AttackPointPercentage(0.3f), AttackFired(false)
{
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	RootComponent = AttackRange;
	AttackRange->InitSphereRadius(Range);
	AttackRange->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnAttackRangeBeginOverlap);
	AttackRange->OnComponentEndOverlap.AddDynamic(this, &ATurret::OnAttackRangeEndOverlap);
	AttackRange->SetGenerateOverlapEvents(true);
	bGenerateOverlapEventsDuringLevelStreaming = 1;
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	SetupRange();
	RecalculateRange();
	RecalculateAgility();
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

void ATurret::OnWatchedEnemyKilled(AEnemy* Enemy, ATurret* TurretInstigator) {
	WatchList.Remove(Enemy);
	if (AimingTarget == Enemy) {
		RefreshTarget();
	}
}

void ATurret::RefreshTarget() {
	if (WatchList.Num()) {
		AimingTarget = WatchList[0];
		AttackPhase = 0.f;
		AttackFired = false;
	}
	
}

bool ATurret::CanAttackEnemy(AEnemy* Enemy) const {
	return GroundAirAbility & Enemy->GroundAirState;
}

ABullet* ATurret::GenerateBullet(AEnemy* Target) {
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Params.Instigator = this;
	auto Bullet = GetWorld()->SpawnActor<ABullet>(ABullet::StaticClass(), GetActorLocation(), GetActorRotation(), Params);
	Bullet->SetTurretOwner(this);
	Bullet->SetTarget(Target);

	for (auto TB : ActiveBuffs) {
		TB->RetrofitBullet(Bullet);
	}
	return Bullet;
}

void ATurret::TickAttack(float DeltaTime) {
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