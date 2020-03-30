// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TurretBuff.h"
#include "Core/Turret.h"
#include "Core/BulletBuff.h"


UTurretBuff::UTurretBuff(const FObjectInitializer& ObjectInitializer) {
	BulletBuffPrototype = UBulletBuff::StaticClass();
}

void UTurretBuff::ApplyToTurret(ATurret* Turret)
{
	BuffOwner = Turret;
	Turret->AddBuff(this);
	OnBeginBuff();
}

void UTurretBuff::OnBeginBuff() {
	ensureAlwaysMsgf(BuffOwner, TEXT("BuffOwner of this TurretBuff cannot be null."));
	for (UTurretBuff* Buff : BuffOwner->ActiveBuffs) {
		if (CanApplyToBuff(Buff)) {
			ApplyToBuff(Buff);
		}
	}
}

void UTurretBuff::OnEndBuff() {
	ensureAlwaysMsgf(BuffOwner, TEXT("BuffOwner of this TurretBuff cannot be null."));
	for (UTurretBuff* Buff : BuffOwner->ActiveBuffs) {
		if (CanApplyToBuff(Buff)) {
			RemoveFromBuff(Buff);
		}
	}
}

bool UTurretBuff::CanApplyToBuff(UTurretBuff* TBuff) {
	if (this == TBuff)
		return false;
	if (CanApplyToBuffPredicate.IsBound()) {
		return CanApplyToBuffPredicate.Execute(TBuff);
	}
	else
		return false;
}

void UTurretBuff::RetrofitBullet(class ABullet* Bullet) {
	if (bUseCount) {
		CountsLeft -= 1;
		if (CountsLeft == 0) {
			OnTurretBuffDestroy.Broadcast(ETurretBuffDestroyReason::FireDepleted);
			DestroyComponent();
		}
	}
	RetrofitBulletMethod.ExecuteIfBound(Bullet);
}

void UTurretBuff::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	if (bHasLimitedTime) {
		float timeElapsed = DeltaTime > DurationLeft ? DurationLeft : DeltaTime;
		DurationLeft -= DeltaTime;
		if (DurationLeft == 0.f) {
			Expire();
		}
	}
}

void UTurretBuff::Expire() {
	OnTurretBuffDestroy.Broadcast(ETurretBuffDestroyReason::TimeUp);
	DestroyComponent();
}

void UTurretBuff::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	ensureAlwaysMsgf(BuffOwner, TEXT("BuffOwner of this TurretBuff cannot be null."));
	UActorComponent::EndPlay(EndPlayReason);
	OnEndBuff();
	BuffOwner->RemoveBuff(this);
	RetrofitBulletMethod.Unbind();
	CanApplyToBuffPredicate.Unbind();
	ApplyToBuffMethod.Unbind();
	RemoveFromBuffMethod.Unbind();
	OnTurretBuffDestroy.Clear();
}
