// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LunePawnBase.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API AEnemy : public ALunePawnBase
{
	GENERATED_BODY()
	
public:
	AEnemy();
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* CollisionVolume;
	
	
};
