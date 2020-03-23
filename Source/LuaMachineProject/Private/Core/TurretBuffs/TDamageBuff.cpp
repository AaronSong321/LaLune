// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TurretBuffs/TDamageBuff.h"


UTDamageBuff::UTDamageBuff(const FObjectInitializer& ObjectInitializer) {
	bUseCount = 0;
	bHasLimitedTime = 0;
	bHasDamage = 1;
	bGenerateBulletBuff = 1;
	bAffectOtherTurretBuffs = 0;
}

