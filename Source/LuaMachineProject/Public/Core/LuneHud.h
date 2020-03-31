// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LuneHud.generated.h"

class UITurretPanel;


/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API ALuneHud : public AHUD
{
	GENERATED_BODY()
public:
	ALuneHud(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
protected:
	UITurretPanel* TurretPanel;
	
	virtual void BeginPlay() override;
	
};
