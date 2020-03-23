// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LunePawnBase.h"
#include "Bullet.generated.h"

class AEnemy;

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API ABullet : public ALunePawnBase
{
	GENERATED_BODY()
		
public:
	ABullet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	class AEnemy* Target;
	float Speed;
	virtual void Tick(float DeltaTime) override;
	virtual void MoveToTarget(float TimeElapsed);
	uint8 bHasDamage : 1;
	float Damage;

};
