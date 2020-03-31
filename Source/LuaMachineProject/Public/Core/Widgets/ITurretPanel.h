// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ITurretPanel.generated.h"

class ATurret;
//class 

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API UITurretPanel : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite) ATurret* Turret;

	
};
