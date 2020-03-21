// Fill out your copyright notice in the Description page of Project Settings.

#include "Development/ConcursusProbatorem.h"
#include "Engine/World.h"
#include "TimerManager.h"



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
	turret1 = GetWorld()->SpawnActor<ATurret>(FVector::ZeroVector, FRotator::ZeroRotator);
	TSubclassOf<AEnemy> WraithClass = LoadClass<AEnemy>(this, TEXT("Blueprint'/Game/CoreObjects/Wraith.Wraith_C'"));
	enemy1 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(100, 0, 100), FRotator::ZeroRotator);
	enemy2 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(20, 0, 20), FRotator::ZeroRotator);
	UE_LOG(LuneProject, Log, TEXT("%s"), *enemy1->GetActorLocation().ToString());
	turret1->AddRangeMul(1.f);
}

void AConcursusProbatorem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	AActor::EndPlay(EndPlayReason);
}

