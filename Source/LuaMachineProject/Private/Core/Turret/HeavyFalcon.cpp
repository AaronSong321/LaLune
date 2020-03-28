// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Turret/HeavyFalcon.h"

#include "Core/TurretBuffs/TDamageBuff.h"
#include "Core/Bullet.h"

AHeavyFalcon::AHeavyFalcon(const FObjectInitializer& ObjectInitializer) :ATurret(ObjectInitializer) {
	Range = 200;
	Agility = 200;
	GroundAirAbility = EGroundAirValue::Ground;
	BulletSpeed = 200;

	//UTDamageBuff* DamageBuff = UObject::CreateDefaultSubobject<UTDamageBuff>(TEXT("PrimaryBuff"));
	//DamageBuff->Damage = 30;
	//DamageBuff->BuffOwner = this;
	//AddBuff(DamageBuff);

	UTDecelerateBuff* DecelerateBuff = UObject::CreateDefaultSubobject<UTDecelerateBuff>(TEXT("DecelerateBuff"));
	DecelerateBuff->Duration = 3;
	DecelerateBuff->SpeedMulLoss = 0.7f;
	DecelerateBuff->SpeedOffsetLoss = 0;
	DecelerateBuff->BuffOwner = this;
	AddBuff(DecelerateBuff);
}



