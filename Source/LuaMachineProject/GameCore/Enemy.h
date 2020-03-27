// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/LunePawnBase.h"
#include "Components/SphereComponent.h"
#include "Core/CommonActors.h"
#include "Enemy.generated.h"


class ATurret;
class AActor;
class USphereComponent;


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
	USphereComponent* CollisionVolume;
	DECLARE_DELEGATE_ThreeParams(FEnemyDamagedSelfSignature, AEnemy*, float, ATurret*);
	// Subclass of AEnemy can bind this delegate to customize enemy behavior (e.g. get in rage when health point is below a threshold). This delegate is guaranteed to be executed before OnEnemyDamaged.
	FEnemyDamagedSelfSignature ProcessGetDamage;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEnemyDamagedSignature, AEnemy*, Enemy, float, Damage, ATurret*, TurretInstigator);
	// Event enemy damaged. Related classes may bind this delegate to collect damage information (e.g. gameplay statistics can gather information and make a damage compendium).
	UPROPERTY(BlueprintAssignable, Category = "Enemy Damaged")
		FEnemyDamagedSignature OnEnemyDamaged;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FEnemyKilledSignature, AEnemy*, Enemy, ATurret*, TurretInstigator);
	// Event enemy killed
	UPROPERTY(BlueprintAssignable, Category = "Enemy Killed")
	FEnemyKilledSignature OnEnemyKilled;

	virtual void HitBy(class ABullet* Bullet);
	UFUNCTION(BlueprintCallable, Category = "Enemy Damaged")
	virtual void TakeBulletDamage(float Amount, ATurret* TurretInstigator, ABullet* Causer);
	// Should change with a real damage type, with damage(float), type(EDamageType) and other information
	UFUNCTION(BlueprintCallable, Category = "Enemy Damaged")
	virtual void TakeDamageTemporary(float Amount, ATurret* TurretInstigator);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roam")
	bool bRoaming = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Roam")
	int32 RoamPhase;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roam")
	int32 RoamTable = 40;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roam")
	FVector RoamDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roam")
	float RoamSpeed = 1000;
	UFUNCTION(BlueprintCallable, Category = "Roam")
	void StartRoaming(FVector Direction = FVector::ForwardVector) {
		RoamDirection = Direction.GetSafeNormal();
		bRoaming = true;
		RoamPhase = 0;
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Roam")
	EGroundAirValue GroundAirState = EGroundAirValue::Ground;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPoint;

};
