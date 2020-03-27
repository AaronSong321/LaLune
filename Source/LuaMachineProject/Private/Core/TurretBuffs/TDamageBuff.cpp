// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TurretBuffs/TDamageBuff.h"
#include "Core/Bullet.h"
#include "Core/BulletBuff.h"
#include "GameCore/Enemy.h"
#include "Core/Turret.h"
#include "GameFramework/Actor.h"


UTDamageBuff::UTDamageBuff(const FObjectInitializer& ObjectInitializer) {
	bUseCount = 0;
	bHasLimitedTime = 0;
	bHasDamage = 1;
	bGenerateBulletBuff = 1;
	bAffectOtherTurretBuffs = 0;
	PrimaryComponentTick.bCanEverTick = false;
	RetrofitBulletMethod.BindUObject(this, &UTDamageBuff::ThisRetrofitBullet);
}

void UTDamageBuff::ThisRetrofitBullet(ABullet* Bullet) {
	UBulletBuff* BBuff = NewObject<UBulletBuff>(BulletBuffPrototype);
	BBuff->SetUseDamage(bHasDamage);
	BBuff->SetBuffOwner(Bullet);
	BBuff->SetDamage(Damage);
	BBuff->OnBulletHitEnemy.BindLambda([](UBulletBuff* Buff, AEnemy* Enemy) {
		Enemy->TakeBulletDamage(Buff->GetDamage(), Buff->GetBuffOwner()->GetTurretOwner(), Buff->GetBuffOwner());
	});
	Bullet->AddBuff(BBuff);
}


