// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LuaMachineProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API ALuaMachineProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	ALuaMachineProjectGameModeBase();


protected:
	virtual void BeginPlay() override;
	
	void TestCreateCollide();

};
