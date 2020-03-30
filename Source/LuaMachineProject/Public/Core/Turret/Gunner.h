// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/Turret.h"
#include "Gunner.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API AGunner : public ATurret
{
	GENERATED_BODY()
	
public:
	AGunner(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	
};
