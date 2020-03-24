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

	UTDamageBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	float Damage;
public:
	virtual bool CanApplyToTurret(ATurret* Turret) const override { return true; }

private:
	void ThisRetrofitBullet(ABullet* Bullet);

};
