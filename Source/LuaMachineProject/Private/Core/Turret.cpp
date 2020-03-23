// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "GameCore/Enemy.h"
#include "Core/Bullet.h"
#include "Core/TurretBuff.h"


ATurret::ATurret(const FObjectInitializer& ObjectInitializer) : ALunePawnBase(ObjectInitializer), DamageOffset(0), DamageAddon(0), DamageMul(1.f), RangeMul(1.f), Damage(20), Range(50), BulletPrototype(ABullet::StaticClass())
{
	UAttackBehavior* attacker1 = CreateDefaultSubobject<UAttackBehavior>(TEXT("Attacker1"), false);
	attacker1->SetAttackBehaviorName(TEXT("Attacker1"));
	Attackers.Add(attacker1);
	AttackRange = CreateDefaultSubobject<USphereComponent>(TEXT("AttackRange"));
	RootComponent = AttackRange;

	RecalculateDamage();
	RecalculateRange();
	AttackRange->InitSphereRadius(Range);
	AttackRange->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	AttackRange->OnComponentBeginOverlap.AddDynamic(this, &ATurret::OnAttackRangeOverlap);
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
	AttackRange->OnComponentBeginOverlap.RemoveDynamic(this, &ATurret::OnAttackRangeOverlap);
}

void ATurret::ReadAttackers()
{
	for (UAttackBehavior* attacker : Attackers) {
		UE_LOG(LuneProject, Log, TEXT("Turret Attacker name: %s"), *attacker->GetUniqueName().ToString());
	}
}

void ATurret::OnAttackRangeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	UE_LOG(LuneProject, Log, TEXT("in %s: %d %d %d %d"), int32(OverlappedComp == AttackRange), enemy != nullptr, OtherBodyIndex, int32(bFromSweep));
}

ABullet* ATurret::GenerateBullet(Enemy* Target) {
	ABullet* Bullet = NewObject<ABullet>(this, ABullet::StaticClass());
	Bullet->Instigator = this;


	for (auto TB : ActiveBuffs) {
		TB->RetrofitBullet(Bullet);
	}
	return Bullet;
}

