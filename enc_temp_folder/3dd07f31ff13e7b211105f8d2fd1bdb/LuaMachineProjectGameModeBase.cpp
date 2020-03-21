// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaMachineProjectGameModeBase.h"
#include "LuaMachine.h"
#include "LuaBlueprintFunctionLibrary.h"
#include "MyLuaState.h"
#include "Core/Turret.h"
#include "TimerManager.h"
#include "GameCore/Enemy.h"
#include "Core/LuneCharacter.h"


DEFINE_LOG_CATEGORY_STATIC(LogProject, Log, All)

ALuaMachineProjectGameModeBase::ALuaMachineProjectGameModeBase()
{
	DefaultPawnClass = ALuneCharacter::StaticClass();

}

void ALuaMachineProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	TestCreateCollide();
}

void ALuaMachineProjectGameModeBase::TestCreateCollide()
{
	ATurret* actor = GetWorld()->SpawnActor<ATurret>(FVector::ZeroVector, FRotator::ZeroRotator);
	FTimerHandle spawnTwoEnemiesHandle;
	FTimerManager& timerSeter = GetWorld()->GetTimerManager();
	timerSeter.SetTimer(spawnTwoEnemiesHandle, [this, &timerSeter, &spawnTwoEnemiesHandle]()->void {
		TSubclassOf<AEnemy> WraithClass = LoadClass<AEnemy>(nullptr, TEXT("Blueprint'/Game/CoreObjects/Wraith.Wraith_C'"));
		AEnemy* enemy1 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(100, 0, 100), FRotator::ZeroRotator);
		AEnemy* enemy2 = GetWorld()->SpawnActor<AEnemy>(WraithClass, FVector(20, 0, 20), FRotator::ZeroRotator);
		UE_LOG(LuneProject, Log, TEXT("%s"), *enemy1->GetActorLocation().ToString());
		GetWorld()->GetTimerManager().ClearTimer(spawnTwoEnemiesHandle);
	}, 1, false, 0.3f);
	FTimerHandle changeTurretChangeHandle;
	timerSeter.SetTimer(changeTurretChangeHandle, [this, &timerSeter, &changeTurretChangeHandle, actor]()->void {
		actor->AddRangeMul(1.f);
		GetWorld()->GetTimerManager().ClearTimer(changeTurretChangeHandle);
	}, 1, false, 0.5f);
}

