// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include "Core/Bullet.h"
#include "Core/Turret.h"
#include "Core/EnemyBuff.h"

AEnemy::AEnemy() :ALunePawnBase() {
	PrimaryActorTick.bCanEverTick = true;
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;
	CollisionVolume->InitSphereRadius(10.f);
	CollisionVolume->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	CollisionVolume->SetGenerateOverlapEvents(true);
	bCanBeDamaged = 1;
	bGenerateOverlapEventsDuringLevelStreaming = 1;
}

void AEnemy::BeginPlay() {
	Super::BeginPlay();
	HealthPoint = MaxHealth;
	CalcSpeed();
}

void AEnemy::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	if (!IsStunned()) {
		if (bRoaming) {
			const FVector Direction = RoamPhase < RoamTable / 2 ? RoamDirection : -RoamDirection;
			if (++RoamPhase == RoamTable) {
				RoamPhase = 0;
			}
			SetActorLocation(GetActorLocation() + Direction*DeltaTime*SpeedActual);
			if (RoamPhase == 0 || RoamPhase == RoamTable / 2) {
				//UE_LOG(LuneProject, Log, TEXT("Enemy roamed to (%s)"), *GetActorLocation().ToString());
			}
		}
	}

	TArray<UEnemyBuff*> RemoveList;
	for (UEnemyBuff* Buff : ActiveBuffs) {
		Buff->OnBuffTick(Buff->EnemyTarget, DeltaTime);
		if (Buff->bLifeCycleExpired) {
			RemoveList.Add(Buff);
		}
	}
	for (UEnemyBuff* Buff : RemoveList) {
		ActiveBuffs.Remove(Buff);
	}
}

void AEnemy::EndPlay(const EEndPlayReason::Type Reason) {
	Super::EndPlay(Reason);
	ProcessGetDamage.Unbind();
	OnEnemyDamaged.Clear();
	OnEnemyKilled.Clear();
	for (UEnemyBuff* Buff : ActiveBuffs) {
		Buff->OnBuffEndPlay(Buff->EnemyTarget, EEnemyBuffEndReason::EnemyDie);
	}
}

void AEnemy::Die(const EEnemyDieReason Reason, ATurret* TurretInstigator) {
	switch (Reason) {
	case EEnemyDieReason::ZeroHealth:
	case EEnemyDieReason::InstantKill:
		break;
	case EEnemyDieReason::ArriveAtDestination:
		break;
	}
	OnEnemyKilled.Broadcast(this, TurretInstigator, Reason);
	Destroy();
}

void AEnemy::HitBy(ABullet* Bullet) {
	//if (Bullet->bHasDamage) {
	//	TakeBulletDamage(Bullet->Damage, Bullet->Instigator, Bullet);
	//}
}

void AEnemy::TakeBulletDamage(float Amount, ATurret* TurretInstigator, ABullet* Causer) {
	float ActualDamage = Amount > HealthPoint ? HealthPoint : Amount;
	TakeDamageTemporary(Amount, TurretInstigator);
}

void AEnemy::TakeDamageTemporary(float Amount, ATurret* TurretInstigator) {
	HealthPoint -= Amount;
	ProcessGetDamage.ExecuteIfBound(this, Amount, TurretInstigator);
	OnEnemyDamaged.Broadcast(this, Amount, TurretInstigator);
	if (HealthPoint == 0.f) {
		Die(EEnemyDieReason::ZeroHealth, TurretInstigator);
	}
}

bool AEnemy::AddBuff(UEnemyBuff* Buff) {
	bool ans = true;
	if (ActiveBuffs.Contains(Buff)) {
		UE_LOG(LuneProject, Error, TEXT("[%s, %d] Such EnemyBuff already exists"), __FUNCTIONW__, __LINE__);
		return false;
	}
	if (Buff->CanApplyToEnemy(this)) {
		bool Incompatibility = false;
		for (UEnemyBuff* B : ActiveBuffs) {
			EEnemyBuffCompatibility Com = Buff->IsCompatibleWith(B);
			switch (Com) {
			case EEnemyBuffCompatibility::Compatible: break;
			case EEnemyBuffCompatibility::DiscardOld: 
				Buff->OverrideBuff(B, Com);
				B->OnBuffEndPlay(B->EnemyTarget, EEnemyBuffEndReason::Discard);
				ActiveBuffs.Remove(B);
				Incompatibility = true;
				break;
			case EEnemyBuffCompatibility::DiscardThis:
			case EEnemyBuffCompatibility::OverrideOld:
				Buff->OverrideBuff(B, Com);
				Incompatibility = true;
				break;
			}
			if (Incompatibility) {
				ans = false;
				break;
			}
		}
		if (ans) {
			ActiveBuffs.Add(Buff);
		}
	}
	else
		ans = false;
	if (ans) {
		Buff->EnemyTarget = this;
		Buff->OnBuffBeginPlay(Buff->EnemyTarget);
	}
	return ans;
}

void AEnemy::RemoveBuff(UEnemyBuff* Buff) {
	ActiveBuffs.Remove(Buff);
}
