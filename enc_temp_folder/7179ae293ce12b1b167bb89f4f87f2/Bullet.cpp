// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "GameCore/Enemy.h"
#include "Core/BulletBuff.h"
#include "CommonActors.h"


ABullet::ABullet(const FObjectInitializer& ObjectInitializer):HitEnemyDistance(30), Speed(1000) {
	PrimaryActorTick.bCanEverTick = true;
}

void ABullet::BeginPlay() {
	Super::BeginPlay();
	for (auto Buff : ActiveBuffs) {
		Buff->RegisterComponent();
	}
}

void ABullet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (Target && Target->IsPendingKill()) {
		UE_LOG(LuneProject, Log, TEXT("Enemy is Pending kill."));
	}
	if (Target && !Target->IsPendingKill()) {
		MoveToTarget(DeltaTime);
		if (FVector::Dist(GetActorLocation(), Target->GetActorLocation()) <= HitEnemyDistance) {
			OnHitEnemy(Target);
		}
	}
	else {
		MoveAfterEnemyDied(DeltaTime);
		if (FVector::Dist(GetActorLocation(), EnemyDieLocation) <= HitEnemyDistance) {
			OnHitLocation(EnemyDieLocation);
		}
	}
}

void ABullet::MoveToTarget(float DeltaTime) {
	const FVector Direction(Target->GetActorLocation() - GetActorLocation());
	SetActorLocation(GetActorLocation() + Direction.GetSafeNormal() * DeltaTime * Speed);
}

void ABullet::MoveAfterEnemyDied(float DeltaTime) {
	const FVector Direction(EnemyDieLocation - GetActorLocation());
	SetActorLocation(GetActorLocation() + Direction.GetSafeNormal()*DeltaTime*Speed);
}

void ABullet::OnHitEnemy(AEnemy* Enemy) {
	for (auto buff : ActiveBuffs) {
		UE_LOG(LuneProject, Log, TEXT("%s %d"), __FUNCTIONW__, __LINE__);
		buff->OnBulletHitEnemy.ExecuteIfBound(buff, Enemy);
	}
	Destroy();
}

void ABullet::OnHitLocation(FVector Location) {
	Destroy();
}

void ABullet::SetTarget(AEnemy* Enemy) {
	Target = Enemy;
	Enemy->OnEnemyKilled.AddDynamic(this, &ABullet::ProcessTargetDieEvent);
}

void ABullet::ProcessTargetDieEvent(AEnemy* Enemy, ATurret* Turret) {
	Target = nullptr;
	EnemyDieLocation = Enemy->GetActorLocation();
}
