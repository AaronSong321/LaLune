// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Core/Bullet.h"
#include "Core/Turret.h"


AEnemy::AEnemy() :ALunePawnBase() {
	PrimaryActorTick.bCanEverTick = true;
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;
	CollisionVolume->InitSphereRadius(10.f);
	CollisionVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionVolume->SetGenerateOverlapEvents(true);
	bCanBeDamaged = 1;
	bGenerateOverlapEventsDuringLevelStreaming = 1;
	
}

void AEnemy::BeginPlay() {
	Super::BeginPlay();
	HealthPoint = MaxHealth;
}

void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (bRoaming) {
		const FVector Direction = RoamPhase < RoamTable / 2 ? RoamDirection : -RoamDirection;
		if (++RoamPhase == RoamTable) {
			RoamPhase = 0;
		}
		SetActorLocation(GetActorLocation() + Direction*DeltaTime*RoamSpeed);
		if (RoamPhase == 0 || RoamPhase == RoamTable / 2) {
			//UE_LOG(LuneProject, Log, TEXT("Enemy roamed to (%s)"), *GetActorLocation().ToString());
		}
	}
}

void AEnemy::EndPlay(const EEndPlayReason::Type Reason) {
	Super::EndPlay(Reason);
	ProcessGetDamage.Unbind();
	OnEnemyDamaged.Clear();
	OnEnemyKilled.Clear();
}

void AEnemy::HitBy(ABullet* Bullet) {
	//if (Bullet->bHasDamage) {
	//	TakeBulletDamage(Bullet->Damage, Bullet->Instigator, Bullet);
	//}
}

void AEnemy::TakeBulletDamage(float Amount, ATurret* TurretInstigator, ABullet* Causer) {
	float ActualDamage = Amount > HealthPoint ? HealthPoint : Amount;
	TakeDamageTemporary(Amount, TurretInstigator);
}

void AEnemy::TakeDamageTemporary(float Amount, ATurret* TurretInstigator) {
	HealthPoint -= Amount;
	UE_LOG(LuneProject, Log, TEXT("Enemy took damage: %f, from: Turret"), Amount);
	ProcessGetDamage.ExecuteIfBound(this, Amount, TurretInstigator);
	OnEnemyDamaged.Broadcast(this, Amount, TurretInstigator);
	if (HealthPoint == 0.f) {
		UE_LOG(LuneProject, Log, TEXT("Enemy die"));
		OnEnemyKilled.Broadcast(this, TurretInstigator);
		Destroy();
	}
}
