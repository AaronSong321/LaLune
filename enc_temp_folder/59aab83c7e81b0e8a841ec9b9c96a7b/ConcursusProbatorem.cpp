// Fill out your copyright notice in the Description page of Project Settings.

#include "Development/ConcursusProbatorem.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameCore/Enemy.h"
#include "Core/Turret.h"
#include "Core/Turret/Gunner.h"


AConcursusProbatorem::AConcursusProbatorem()
{

}

void AConcursusProbatorem::BeginPlay() {
	AActor::BeginPlay();
	TestCollide2();
}

void AConcursusProbatorem::TestCollide() {
	turret1 = GetWorld()->SpawnActor<ATurret>(FVector::ZeroVector, FRotator::ZeroRotator);
	FTimerHandle spawnTwoEnemiesHandle;
	FTimerManager& timerSeter = GetWorld()->GetTimerManager();
	timerSeter.SetTimer(spawnTwoEnemiesHandle, [this, &timerSeter, &spawnTwoEnemiesHandle]()->void {
		TSubclassOf<AEnemy> WraithClass = LoadClass<AEnemy>(nullptr, TEXT("Blueprint'/Game/CoreObjects/Wraith.Wraith_C'"));
		enemy1 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(100, 0, 100), FRotator::ZeroRotator);
		enemy2 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(20, 0, 20), FRotator::ZeroRotator);
		UE_LOG(LuneProject, Log, TEXT("%s"), *enemy1->GetActorLocation().ToString());
		GetWorld()->GetTimerManager().ClearTimer(spawnTwoEnemiesHandle);
	}, 1, false, 0.3f);
	FTimerHandle changeTurretChangeHandle;
	timerSeter.SetTimer(changeTurretChangeHandle, [this, &timerSeter, &changeTurretChangeHandle]()->void {
		turret1->AddRangeMul(1.f);
		GetWorld()->GetTimerManager().ClearTimer(changeTurretChangeHandle);
	}, 1, false, 0.5f);
}

void AConcursusProbatorem::TestCollide2() {
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	turret1 = GetWorld()->SpawnActor<ATurret>(AGunner::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator, Params);
	TSubclassOf<AEnemy> WraithClass = LoadClass<AEnemy>(this, TEXT("Blueprint'/Game/CoreObjects/Wraith.Wraith_C'"));
	enemy1 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(100, 100, 0), FRotator::ZeroRotator, Params);
	enemy2 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(100, 100, 0), FRotator::ZeroRotator, Params);
	UE_LOG(LuneProject, Log, TEXT("%s"), *enemy2->GetActorLocation().ToString());
	enemy1->StartRoaming(FVector(1, 1, 0));
	enemy2->SetActorLocation(FVector(1, 1, 0));
	turret1->AddRangeMul(3.f);

	FTimerHandle PrintEnemiesLocation;
	FTimerManager& TimerSeter = GetWorld()->GetTimerManager();
	TimerSeter.SetTimer(PrintEnemiesLocation, [this]() {
		//UE_LOG(LuneProject, Log, TEXT("Enemy1:(%s), Enemy2:(%s)"), *enemy1->GetActorLocation().ToString(), *enemy2->GetActorLocation().ToString()); 
	}, 0.5f, true, 0.05f);
}

void AConcursusProbatorem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor::EndPlay(EndPlayReason);
}

