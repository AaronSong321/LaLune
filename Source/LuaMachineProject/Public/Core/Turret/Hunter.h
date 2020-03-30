// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Turret.h"
#include "Hunter.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API AHunter : public ATurret
{
	GENERATED_BODY()
	
public:
	AHunter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	
};
