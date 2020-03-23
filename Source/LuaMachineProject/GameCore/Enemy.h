// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LunePawnBase.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

class ATurret;


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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemyKilledSignature, ATurret*, Turret, AEnemy*, Enemy);
	FEnemyKilledSignature OnEnemyKilled;

	virtual void HitBy(class ABullet* Bullet);
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void TakeDamage(float Amount, class APawn* Instigator, class AActor* Causer);
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

};
