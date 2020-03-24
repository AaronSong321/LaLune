// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "GameCore/Enemy.h"
#include "Core/Bullet.h"
#include "Core/TurretBuff.h"
#include "Core/AttackBehavior.h"


ATurret::ATurret(const FObjectInitializer& ObjectInitializer) : ALunePawnBase(ObjectInitializer), DamageOffset(0), DamageAddon(0), DamageMul(1.f), RangeMul(1.f), Damage(20), Range(50), BulletPrototype(ABullet::StaticClass())
{
	RecalculateDamage();
	RecalculateRange();

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
	AEnemy* enemy = Cast<AEnemy>(OtherActor);

}

void ATurret::OnAttackRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
}

bool ATurret::CanAttackEnemy(AEnemy* Enemy) const {
	return true;
}

ABullet* ATurret::GenerateBullet(AEnemy* Target) {
	ABullet* Bullet = NewObject<ABullet>(this, ABullet::StaticClass());
	Bullet->Instigator = this;


	for (auto TB : ActiveBuffs) {
		TB->RetrofitBullet(Bullet);
	}
	return Bullet;
}

