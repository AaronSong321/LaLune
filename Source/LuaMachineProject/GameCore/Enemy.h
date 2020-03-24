// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LunePawnBase.h"
#include "Components/SphereComponent.h"
#include "Enemy.generated.h"

class ATurret;
class AActor;

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API AEnemy : public ALunePawnBase
{
	GENERATED_BODY()
	
public:
	AEnemy();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USphereComponent* CollisionVolume;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemyKilledSignature, ATurret*, Turret, AEnemy*, Enemy);
	UPROPERTY(BlueprintAssignable, Category = "Enemy")
	FEnemyKilledSignature OnEnemyKilled;

	virtual void HitBy(class ABullet* Bullet);
	//virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void TakeBulletDamage(float Amount, AActor* Instigator, AActor* Causer);

private:
	bool bRoaming = false;
	int32 RoamPhase;
public:
	int32 RoamTable = 40;
	FVector RoamDirection;
	float RoamSpeed = 1000;
	void StartRoaming(FVector Direction = FVector::ForwardVector) {
		RoamDirection = Direction.GetSafeNormal();
		bRoaming = true;
		RoamPhase = 0;
	}
};
