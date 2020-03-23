// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Core/Bullet.h"
#include "Core/Turret.h"


AEnemy::AEnemy() :ALunePawnBase() {
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;
	CollisionVolume->InitSphereRadius(10.f);
	CollisionVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionVolume->SetGenerateOverlapEvents(true);
	bCanBeDamaged = 1;
	bGenerateOverlapEventsDuringLevelStreaming = 1;
	
}

void AEnemy::EndPlay(const EEndPlayReason::Type Reason) {
	Super::EndPlay(Reason);
}

void AEnemy::HitBy(ABullet* Bullet) {
	if (Bullet->bHasDamage) {
		TakeDamage(Bullet->Damage, Bullet->Instigator, Bullet);
	}
}

void AEnemy::TakeDamage(float Amount, APawn* Instigator, AActor* Causer) {
	ATurret* Turret = Cast<ATurret>(Instigator);
	ABullet* Bullet = Cast<ABullet>(Causer);

}
