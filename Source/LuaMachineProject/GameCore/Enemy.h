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
class UEnemyBuff;


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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FEnemyKilledSignature, AEnemy*, Enemy, ATurret*, TurretInstigator, const EEnemyDieReason, Reason);
	// Event enemy killed
	UPROPERTY(BlueprintAssignable, Category = "Life Cycle")
	FEnemyKilledSignature OnEnemyKilled;
	virtual void Die(const EEnemyDieReason Reason, ATurret* TurretInstigator);

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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float Speed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float SpeedOffset = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float SpeedMul = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
		float SpeedActual;
public:
	UFUNCTION(BlueprintCallable, Category = "Speed") void SetSpeed(float NewSpeed) { Speed = NewSpeed; CalcSpeed(); }
	UFUNCTION(BlueprintCallable, Category = "Speed")
		void AddSpeedMul(float Mul) { SpeedMul += Mul; CalcSpeed(); }
	UFUNCTION(BlueprintCallable, Category = "Speed")
		void CalcSpeed() { SpeedActual = (Speed + SpeedOffset)*SpeedMul; }
	UFUNCTION(BlueprintCallable, Category = "Speed")
		void AddSpeedOffset(float Offset) { SpeedOffset += Offset; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stun")
		uint8 StunLock = 0;
public:
	UFUNCTION(BlueprintCallable, Category = "Stun")
		bool IsStunned() { return StunLock != 0; }
	UFUNCTION(BlueprintCallable, Category = "Stun")
		void AddStunLock() { ++StunLock; }
	UFUNCTION(BlueprintCallable, Category = "Stun")
		void RemoveStunLock() { --StunLock; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Buff")
		TArray<UEnemyBuff*> ActiveBuffs;
public:
	// Add the EnemyBuff to the Enemy, the "on" method of this EnemyBuff is going to execute until next Tick.
	// Returns true if this buff is successfully added, false if an incompatible buff already exists on this enemy.
	UFUNCTION(BlueprintCallable, Category = "Enemy Buff")
		bool AddBuff(UEnemyBuff* Buff);
	UFUNCTION(BlueprintCallable, Category = "Enemy Buff")
		void RemoveBuff(UEnemyBuff* Buff);
};
