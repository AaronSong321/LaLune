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
	// Tick function should not be called explicitly
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Bullet Target")
	AEnemy* Target;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Owner")
	ATurret* TurretOwner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBulletBuff*> ActiveBuffs;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bullet Target")
	FVector EnemyDieLocation;

public:
	UPROPERTY(EditAnywhere, Category = "Collision Detection")
	float HitEnemyDistance = 30.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Move")
	float Speed;

	UFUNCTION(BlueprintCallable, Category = "Bullet Target")
	virtual void MoveToTarget(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Bullet Target")
	virtual void MoveAfterEnemyDied(float DeltaTime);
	UFUNCTION(BlueprintCallable, Category = "Bullet Target")
	virtual void OnHitEnemy(AEnemy* Enemy);
	UFUNCTION(BlueprintCallable, Category = "Bullet Target")
	virtual void OnHitLocation(FVector Location);
	// Set the target of this bullet to move to and register the enemy's die event
	UFUNCTION(BlueprintCallable, Category = "Bullet Target")
	virtual void SetTarget(AEnemy* NewTarget);
	UFUNCTION(BlueprintCallable, Category = "Bullet Target")
	AEnemy* GetTarget() const { return Target; }
	UFUNCTION(BlueprintCallable, Category = "Owner")
	void SetTurretOwner(ATurret* NewTurretOwner) {
		TurretOwner = NewTurretOwner;
	}
	UFUNCTION(BlueprintCallable, Category = "Owner")
	ATurret* GetTurretOwner()const { return TurretOwner; }

	UFUNCTION(BlueprintCallable, Category = "Bullet Target")
	virtual void ProcessTargetDieEvent(AEnemy* Enemy, ATurret* Turret);
	UFUNCTION(BlueprintCallable, Category = "Bullet Buff")
	void AddBuff(UBulletBuff* Buff) {
		ActiveBuffs.Add(Buff);
	}
	UFUNCTION(BlueprintCallable, Category = "Bullet Buff")
	void RemoveBuff(UBulletBuff* Buff) {
		ActiveBuffs.Remove(Buff);
	}

};
