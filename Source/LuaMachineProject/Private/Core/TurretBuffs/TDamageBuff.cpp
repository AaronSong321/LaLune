// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TurretBuffs/TDamageBuff.h"
#include "GameFramework/Actor.h"
#include "Core/Bullet.h"
#include "Core/BulletBuff.h"
#include "GameCore/Enemy.h"
#include "Core/Turret.h"
#include "Core/EnemyBuff.h"

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

UTDecelerateBuff::UTDecelerateBuff(const FObjectInitializer& ObjectInitializer) {
	bUseCount = 0;
	bHasLimitedTime = 0;
	bHasDamage = 0;
	bGenerateBulletBuff = 1;
	bAffectOtherTurretBuffs = 0;
	PrimaryComponentTick.bCanEverTick = false;
	RetrofitBulletMethod.BindUObject(this, &UTDecelerateBuff::ThisRetrofitBullet);
}

void UTDecelerateBuff::ThisRetrofitBullet(ABullet* Bullet) {
	UBulletBuff* DBuff = NewObject<UBulletBuff>(BulletBuffPrototype);
	DBuff->SetUseDamage(bHasDamage);
	DBuff->SetBuffOwner(Bullet);
	DBuff->OnBulletHitEnemy.BindLambda([this](UBulletBuff* Buff, AEnemy* Enemy) {
		UEDecelerateBuff* EBuff = NewObject<UEDecelerateBuff>(UEDecelerateBuff::StaticClass());
		EBuff->SetDuration(Duration);
		EBuff->SpeedMulLoss = SpeedMulLoss;
		EBuff->SpeedOffsetLoss = SpeedOffsetLoss;
		Enemy->AddBuff(EBuff);
	});
	Bullet->AddBuff(DBuff);
}

