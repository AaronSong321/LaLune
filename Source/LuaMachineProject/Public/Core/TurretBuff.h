// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurretBuff.generated.h"

class ATurret;
class ABullet;
class UBulletBuff;


UENUM()
enum class ETurretBuffDestroyReason :uint8 {
	TurretDestroyed,
	FireDepleted,
	TimeUp,
	SuperAbilityUpgraded,
	SuperAbilityDisabled
};

/**
 * 
 */
UCLASS(Abstract, Category = "Buff|Turret Buff")
class LUAMACHINEPROJECT_API UTurretBuff : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UTurretBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:
	ATurret* BuffOwner;

	// If true, this buff expires after a certain amount of fires
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		uint8 bUseCount : 1;
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		int32 MaxCount;
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		int32 CountsLeft;
	// If true, this buff expires after a finite spell of time
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		uint8 bHasLimitedTime : 1;
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		float MaxDuration;
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		float DurationLeft;
	// If true, this buff can apply damage, and can be affected by damage mutating buffs
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		uint8 bHasDamage : 1;
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		uint8 bGenerateBulletBuff : 1;
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
		uint8 bAffectOtherTurretBuffs : 1;
	UPROPERTY(EditAnywhere, Category = "Buff|Turret Buff")
	TSubclassOf<UBulletBuff> BulletBuffPrototype;


public:
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
	virtual bool CanApplyToTurret(ATurret* Turret) const { return false; }
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
	virtual void ApplyToTurret(ATurret* Turret);
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
		virtual void OnBeginBuff();
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
		virtual void OnEndBuff();
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
		void Expire();

	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
	virtual void RetrofitBullet(ABullet* Bullet);
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
	virtual bool CanApplyToBuff(UTurretBuff* TBuff);
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
	virtual void ApplyToBuff(UTurretBuff* TBuff) {
		ApplyToBuffMethod.ExecuteIfBound(TBuff);
	}
	UFUNCTION(BlueprintCallable, Category = "Buff|Turret Buff")
	virtual void RemoveFromBuff(UTurretBuff* TBuff) {
		RemoveFromBuffMethod.ExecuteIfBound(TBuff);
	}

	DECLARE_DELEGATE_OneParam(FRetrofitBulletSignature, ABullet*);
	FRetrofitBulletSignature RetrofitBulletMethod;
	DECLARE_DELEGATE_RetVal_OneParam(bool, FCanApplyToBuffSignature, UTurretBuff*);
	FCanApplyToBuffSignature CanApplyToBuffPredicate;
	DECLARE_DELEGATE_OneParam(FApplyToBuffSignature, UTurretBuff*);
	FApplyToBuffSignature ApplyToBuffMethod;
	DECLARE_DELEGATE_OneParam(FRemoveFromBuffSignature, UTurretBuff*);
	FRemoveFromBuffSignature RemoveFromBuffMethod;

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurretBuffDestroySignature, const ETurretBuffDestroyReason, Reason);
	UPROPERTY(BlueprintAssignable, Category = "Buff|Turret Buff")
	FTurretBuffDestroySignature OnTurretBuffDestroy;
	//DECLARE_EVENT_OneParam(UTurretBuff, FTurretBuffDestroyEvent, const ETurretBuffDestroyReason);
	//FTurretBuffDestroyEvent OnDestroy;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
