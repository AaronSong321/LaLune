// Fill out your copyright notice in the Description page of Project Settings.

#include "Development/ConcursusProbatorem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameCore/Enemy.h"
#include "Core/Turret.h"
#include "Core/Turret/Gunner.h"
#include "Core/Turret/HeavyFalcon.h"
#include "Core/Turret/Hunter.h"

AConcursusProbatorem::AConcursusProbatorem()
{

}

void AConcursusProbatorem::BeginPlay() {
	AActor::BeginPlay();
	TestCollide2();
}

void AConcursusProbatorem::TestCollide2() {
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	turret1 = GetWorld()->SpawnActor<ATurret>(AGunner::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);
	TSubclassOf<AEnemy> WraithClass = LoadClass<AEnemy>(this, TEXT("Blueprint'/Game/CoreObjects/Wraith.Wraith_C'"));
	enemy1 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(200, 400, 0), FRotator::ZeroRotator, Params);
	enemy2 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(-300, 600, 0), FRotator::ZeroRotator, Params);
	enemy1->StartRoaming(FVector(1, 0.5, 0));
	enemy1->SetSpeed(600);
	enemy1->RoamTable = 100;
	enemy2->StartRoaming(FVector(0, -1, 0));
	enemy2->SetSpeed(600);
	//auto turret2 = GetWorld()->SpawnActor<ATurret>(AHeavyFalcon::StaticClass(), FVector(0, 400, 0), FRotator::ZeroRotator, Params);
	//turret2->AddRangeMul(3);
	//turret1->AddRangeMul(3);
	auto Hunter3 = GetWorld()->SpawnActor<AHunter>(AHunter::StaticClass(), FVector(300, 300, 0), FRotator::ZeroRotator, Params);
	Hunter3->SetAgility(400);
}

void AConcursusProbatorem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor::EndPlay(EndPlayReason);
}

