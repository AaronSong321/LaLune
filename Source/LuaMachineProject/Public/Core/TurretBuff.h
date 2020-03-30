// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Core/CommonActors.h"
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
UCLASS(Abstract, Category = "Turret Buff")
class LUAMACHINEPROJECT_API UTurretBuff : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UTurretBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:
	// If true, this buff expires after a certain amount of fires
	UPROPERTY(EditAnywhere, Category = "Turret Buff|Tag")
		uint8 bUseCount : 1;
	UPROPERTY(EditAnywhere, Category = "Turret Buff")
		int32 MaxCount;
	UPROPERTY(EditAnywhere, Category = "Turret Buff")
		int32 CountsLeft;
	// If true, this buff expires after a finite spell of time
	UPROPERTY(EditAnywhere, Category = "Turret Buff|Tag")
		uint8 bHasLimitedTime : 1;
	UPROPERTY(EditAnywhere, Category = "Turret Buff")
		float MaxDuration;
	UPROPERTY(EditAnywhere, Category = "Turret Buff")
		float DurationLeft;
	UPROPERTY(EditAnywhere, Category = "Turret Buff|Tag")
		uint8 bGenerateBulletBuff : 1;
	UPROPERTY(EditAnywhere, Category = "Turret Buff|Tag")
		uint8 bAffectOtherTurretBuffs : 1;
	UPROPERTY(EditAnywhere, Category = "Turret Buff")
	TSubclassOf<UBulletBuff> BulletBuffPrototype;

	// If true, this buff is carried by the turret itself and should not be striped from the turret.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Tag")
		bool bTurretDefault;
	// If true, this buff will be displayed in the turret's buff list UI. Note that a TurretDefault TurretBuff should not be displayed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Tag")
		bool bDisplayInBuffList;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Owner")
	ATurret* BuffOwner;
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	virtual bool CanApplyToTurret(ATurret* Turret) const { return true; }
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	virtual void ApplyToTurret(ATurret* Turret);
	UFUNCTION(BlueprintCallable, Category = "Turret Buff")
		virtual void OnBeginBuff();
	UFUNCTION(BlueprintCallable, Category = "Turret Buff")
		virtual void OnEndBuff();
	UFUNCTION(BlueprintCallable, Category = "Turret Buff")
		void Expire();
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	virtual void RetrofitBullet(ABullet* Bullet);
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	virtual bool CanApplyToBuff(UTurretBuff* TBuff);
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	virtual void ApplyToBuff(UTurretBuff* TBuff) {
		ApplyToBuffMethod.ExecuteIfBound(TBuff);
	}
	UFUNCTION(BlueprintCallable, Category = "Turret Buff")
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
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTurretBuffDestroySignature, const ETurretBuffDestroyReason, Reason);
	UPROPERTY(BlueprintAssignable, Category = "Turret Buff")
	FTurretBuffDestroySignature OnTurretBuffDestroy;
	//DECLARE_EVENT_OneParam(UTurretBuff, FTurretBuffDestroyEvent, const ETurretBuffDestroyReason);
	//FTurretBuffDestroyEvent OnDestroy;

};
