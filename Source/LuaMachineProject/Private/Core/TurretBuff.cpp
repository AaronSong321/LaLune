// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/TurretBuff.h"
#include "Core/Turret.h"

UTurretBuff::UTurretBuff(const FObjectInitializer& ObjectInitializer) {

}

void UTurretBuff::ApplyToTurret(ATurret* Turret)
{
	BuffOwner = Turret;
	Turret->AddBuff(this);
	OnBeginBuff();
}

void UTurretBuff::RetrofitBullet(class ABullet* Bullet) {
	if (bUseCount) {
		CountsLeft -= 1;
		if (CountsLeft == 0) {
			OnTurretBuffDestroy.Broadcast(ETurretBuffDestroyReason::FireDepleted);
			DestroyComponent();
		}
	}
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
	OnEndBuff();
	BuffOwner->RemoveBuff(this);
}

