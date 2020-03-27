// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/Turret/Gunner.h"

#include "UObject/ConstructorHelpers.h"

#include "Core/TurretBuffs/TDamageBuff.h"
#include "Core/Bullet.h"

AGunner::AGunner(const FObjectInitializer& ObjectInitializer) :ATurret(ObjectInitializer) {
	Range = 200;
	Agility = 200;
	GroundAirAbility = EGroundAirValue::Ground;
	BulletSpeed = 200;

	UTDamageBuff* DamageBuff = UObject::CreateDefaultSubobject<UTDamageBuff>(TEXT("PrimaryBuff"));
	DamageBuff->Damage = 30;
	DamageBuff->BuffOwner = this;
	AddBuff(DamageBuff);

	static ConstructorHelpers::FClassFinder<ABullet> BulletVisual(TEXT("Blueprint'/Game/CoreObjects/BulletVis.BulletVis_C'"));
	BulletPrototype = BulletVisual.Class;
}


