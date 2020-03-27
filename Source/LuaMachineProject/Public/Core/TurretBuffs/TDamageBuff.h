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
UCLASS()
class LUAMACHINEPROJECT_API UTDamageBuff : public UTurretBuff
{
	GENERATED_BODY()

public:
	UTDamageBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Damage")
	float Damage;
public:
	virtual bool CanApplyToTurret(ATurret* Turret) const override { return true; }

private:
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	void ThisRetrofitBullet(ABullet* Bullet);

};
