// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TurretBuff.h"
#include "TDamageBuff.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API UTDamageBuff : public UTurretBuff
{
	GENERATED_BODY()

	UTDamageBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	virtual bool CanApplyToTurret(ATurret* Turret) const override { return true; }
	virtual void RetrofitBullet(class ABullet* Bullet) override {}
	
	
};
