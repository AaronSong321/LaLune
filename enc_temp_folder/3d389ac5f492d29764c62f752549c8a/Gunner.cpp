// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Turret/Gunner.h"
#include "Core/TurretBuffs/TDamageBuff.h"


AGunner::AGunner(const FObjectInitializer& ObjectInitializer) :ATurret(ObjectInitializer) {
	Range = 200;
	Agility = 200;
	GroundAirAbility = EGroundAirValue::Ground;

	UTDamageBuff* DamageBuff = UObject::CreateDefaultSubobject<UTDamageBuff>(TEXT("PrimaryBuff"));
	DamageBuff->Damage = 30;
	DamageBuff->BuffOwner = this;
	AddBuff(DamageBuff);
}


