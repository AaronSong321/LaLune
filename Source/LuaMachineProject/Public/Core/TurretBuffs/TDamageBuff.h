// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TurretBuff.h"
#include "TDamageBuff.generated.h"

class ATurret;
class ABullet;


/**
 * 
 */
UCLASS(Category = "Turret Buff|Damage Buff")
class LUAMACHINEPROJECT_API UTDamageBuff : public UTurretBuff
{
	GENERATED_BODY()

public:
	UTDamageBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Damage Buff")
	float Damage;
public:
	virtual bool CanApplyToTurret(ATurret* Turret) const override { return true; }

private:
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	void ThisRetrofitBullet(ABullet* Bullet);

};

UCLASS(Category = "Turret Buff|Decelerate Buff")
class LUAMACHINEPROJECT_API UTDecelerateBuff : public UTurretBuff
{
	GENERATED_BODY()

public:
	UTDecelerateBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Decelerate Buff")
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Decelerate Buff")
		float SpeedOffsetLoss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Decelerate Buff")
		float SpeedMulLoss;

public:
	virtual bool CanApplyToTurret(ATurret* Turret) const override { return true; }

private:
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
		void ThisRetrofitBullet(ABullet* Bullet);

};
