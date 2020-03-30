// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyBuff.h"
#include "CommonActors.h"
#include "GameCore/Enemy.h"

// Sets default values for this component's properties
UEnemyBuff::UEnemyBuff(const FObjectInitializer& Initializer) : UObject(Initializer)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	UniqueBuffName = FString("EnemyBuff_GeneralClass");
}


// Called when the game starts
void UEnemyBuff::OnBuffBeginPlay(AEnemy* Enemy)
{
	TimeLeft = Duration;
	if (EnemyTarget) {
		EnemyBuffBeginPlayMethod.ExecuteIfBound(EnemyTarget);
		LOGFL();
	}
	else {
		UE_LOG(LuneProject, Warning, TEXT("This EnemyBuff has no Target during BeginPlay"));
	}
}


// Called every frame
void UEnemyBuff::OnBuffTick(AEnemy* Enemy, float DeltaTime)
{
	float Time = DeltaTime > TimeLeft ? TimeLeft : DeltaTime;
	TimeLeft -= Time;
	if (EnemyTarget)
		EnemyBuffTickMethod.ExecuteIfBound(EnemyTarget, Time);
	else
		UE_LOG(LuneProject, Warning, TEXT("This EnemyBuff has no Target during TickComponent"));
	if (TimeLeft == 0.f) {
		OnBuffEndPlay(Enemy, EEnemyBuffEndReason::TimesUp);
		bLifeCycleExpired = true;
	}
}

void UEnemyBuff::OnBuffEndPlay(AEnemy* Enemy, const EEnemyBuffEndReason Reason) {
	if (EnemyTarget) {
		EnemyBuffEndPlayMethod.ExecuteIfBound(Enemy, Reason);
		LOGFL();
	}
	else
		UE_LOG(LuneProject, Warning, TEXT("This EnemyBuff has no Target during EndPlay"));
	CanApplyToEnemyMethod.Unbind();
	IsCompatibleWithMethod.Unbind();
	OverrideBuffMethod.Unbind();
	EnemyBuffBeginPlayMethod.Unbind();
	EnemyBuffTickMethod.Unbind();
	EnemyBuffEndPlayMethod.Unbind();
}


UEDecelerateBuff::UEDecelerateBuff(const FObjectInitializer& Initializer) :UEnemyBuff(Initializer) {
	UniqueBuffName = FString("Deceleration_GeneralClass");
	EnemyBuffBeginPlayMethod.BindLambda([this](AEnemy* Enemy) {
		Enemy->AddSpeedOffset(-SpeedOffsetLoss);
		Enemy->AddSpeedMul(-SpeedMulLoss);
	});
	EnemyBuffEndPlayMethod.BindLambda([this](AEnemy* Enemy, const EEnemyBuffEndReason Reason) {
		Enemy->AddSpeedOffset(SpeedOffsetLoss);
		Enemy->AddSpeedMul(SpeedMulLoss);
	});
}


void UEDecelerateBuff::OverrideBuff(UEnemyBuff* OtherBuff, const EEnemyBuffCompatibility ConflictType) {
	if (ConflictType == EEnemyBuffCompatibility::OverrideOld) {
		if (UEDecelerateBuff* OtherBuffOfThisClass = Cast<UEDecelerateBuff>(OtherBuff)) {
			OtherBuff->Duration = FMath::Max(Duration, OtherBuff->Duration);
			OtherBuff->TimeLeft = FMath::Max(Duration, OtherBuff->TimeLeft);
		}
	}
}

UEStunBuff::UEStunBuff(const FObjectInitializer& Initializer) {
	UniqueBuffName = TEXT("Stun_GeneralClass");
	EnemyBuffBeginPlayMethod.BindLambda([](AEnemy* Enemy) {
		Enemy->AddStunLock();
	});
	EnemyBuffEndPlayMethod.BindLambda([](AEnemy* Enemy, const EEnemyBuffEndReason Reason) {
		Enemy->RemoveStunLock();
	});
}

void UEStunBuff::OverrideBuff(UEnemyBuff* OtherBuff, const EEnemyBuffCompatibility ConflictType) {
	if (ConflictType == EEnemyBuffCompatibility::OverrideOld) {
		if (UEStunBuff* OtherBuffOfThisClass = Cast<UEStunBuff>(OtherBuff)) {
			OtherBuff->Duration = FMath::Max(Duration, OtherBuff->Duration);
			OtherBuff->TimeLeft = FMath::Max(Duration, OtherBuff->TimeLeft);
		}
	}
}

