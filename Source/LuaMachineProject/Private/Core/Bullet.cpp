// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "GameCore/Enemy.h"

ABullet::ABullet(const FObjectInitializer& ObjectInitializer) {

}

void ABullet::Tick(float DeltaTime) {
	if (!Target->IsPendingKill()) {
		MoveToTarget(DeltaTime);
	}
}

void ABullet::MoveToTarget(float TimeElapsed) {
	const FVector Direction(Target->GetActorLocation() - GetActorLocation());
	SetActorLocation(GetActorLocation() + Direction * TimeElapsed * Speed);
}

