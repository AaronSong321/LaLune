// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Turret/Hunter.h"

#include "Core/TurretBuffs/TDamageBuff.h"
#include "Core/Bullet.h"

AHunter::AHunter(const FObjectInitializer& ObjectInitializer) :ATurret(ObjectInitializer) {
	Range = 270;
	Agility = 60;
	AttackPointPercentage = 0.5;
	GroundAirAbility = EGroundAirValue::GroundAir;
	BulletSpeed = 200;

	UTDamageBuff* DamageBuff = UObject::CreateDefaultSubobject<UTDamageBuff>(TEXT("PrimaryBuff"));
	DamageBuff->SetDamage(60);
	DamageBuff->SetDamage(3);//for test
	DamageBuff->bTurretDefault = true;
	DamageBuff->bDisplayInBuffList = false;
	AddBuff(DamageBuff);

	UTStunBuff* StunBuff = UObject::CreateDefaultSubobject<UTStunBuff>(TEXT("StunBuff"));
	StunBuff->Possibility = 0.15f;
	StunBuff->Duration = 1;
	StunBuff->bTurretDefault = true;
	StunBuff->bDisplayInBuffList = false;
	AddBuff(StunBuff);
}


