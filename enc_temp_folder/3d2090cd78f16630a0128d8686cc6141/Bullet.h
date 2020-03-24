// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LunePawnBase.h"
#include "Bullet.generated.h"

class AEnemy;
class UBulletBuff;
class ATurret;

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API ABullet : public ALunePawnBase
{
	GENERATED_BODY()
		
public:
	ABullet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	ATurret* Owner;
	AEnemy* Target;
	float Speed;
	uint8 bHasDamage : 1;
	float Damage;
	TArray<UBulletBuff*> ActiveBuffs;

	// Tick function should not be called explicitly
	virtual void Tick(float DeltaTime) override;
	virtual void MoveToTarget(float DeltaTime);
	virtual void MoveAfterEnemyDied(float DeltaTime);
	virtual void OnHitEnemy(AEnemy* Enemy);
	// Set the target of this bullet to move to and register the enemy's die event
	virtual void SetTarget(AEnemy* Target);
	virtual void ProcessTargetDieEvent(ATurret* Turret, AEnemy* Enemy);
private:
	FVector EnemyDieLocation;
};
