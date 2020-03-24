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
	OnEnemyKilled.Clear();
}

void AEnemy::HitBy(ABullet* Bullet) {
	//if (Bullet->bHasDamage) {
	//	TakeBulletDamage(Bullet->Damage, Bullet->Instigator, Bullet);
	//}
}

void AEnemy::TakeBulletDamage(float Amount, AActor* Instigator, AActor* Causer) {
	ATurret* Turret = Cast<ATurret>(Instigator);
	ABullet* Bullet = Cast<ABullet>(Causer);

}
