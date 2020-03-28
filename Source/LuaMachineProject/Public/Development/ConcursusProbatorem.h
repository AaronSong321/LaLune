// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LuneActorBase.h"
#include "ConcursusProbatorem.generated.h"

class AEnemy;
class ATurret;


/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API AConcursusProbatorem : public ALuneActorBase
{
	GENERATED_BODY()
	
public:
	AConcursusProbatorem();
protected:
	virtual void BeginPlay() override;
public:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:
	UFUNCTION(BlueprintCallable, Category = "Development Test")
		void TestCollide2();

	UPROPERTY(EditAnywhere, Category = "Development Test")
		AEnemy* enemy1;
	UPROPERTY(EditAnywhere, Category = "Development Test")
		AEnemy* enemy2;
	UPROPERTY(EditAnywhere, Category = "Development Test")
		ATurret* turret1;
	
	
};
