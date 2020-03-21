// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"


AEnemy::AEnemy() :ALunePawnBase() {
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;
	CollisionVolume->InitSphereRadius(10.f);
	CollisionVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionVolume->SetGenerateOverlapEvents(true);
	bCanBeDamaged = 1;
	bGenerateOverlapEventsDuringLevelStreaming = 1;
	
}

