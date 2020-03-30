// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Core/CommonActors.h"
#include "EnemyBuff.generated.h"

class AEnemy;



UCLASS()
class LUAMACHINEPROJECT_API UEnemyBuff : public UObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyBuff(const FObjectInitializer& Initializer = FObjectInitializer::Get());

		
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Identifier")
	FString UniqueBuffName;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Target")
	AEnemy* EnemyTarget;
	UPROPERTY(EditAnywhere, Category = "Duration")
		float Duration;
	UPROPERTY(VisibleAnywhere, Category = "Duration")
		float TimeLeft;
	UPROPERTY(EditAnywhere, Category = "Active")
		bool bLogicallyDisabled = false;
	UPROPERTY(EditAnywhere, Category = "Active")
		bool bLogicallyDelayed = false;

public:
	UFUNCTION(BlueprintCallable, Category = "Duration") void SetDuration(float NewDuration) { Duration = NewDuration; }

	// Bind this delegate to change what type of enemies this buff can bind to
	DECLARE_DELEGATE_RetVal_OneParam(bool, FCanApplyToEnemySignature, AEnemy*);
	FCanApplyToEnemySignature CanApplyToEnemyMethod;
	DECLARE_DELEGATE_RetVal_OneParam(EEnemyBuffCompatibility, FIsCapatibleWithSignature, UEnemyBuff*);
	FIsCapatibleWithSignature IsCompatibleWithMethod;
	DECLARE_DELEGATE_TwoParams(FOverrideBuffSignature, UEnemyBuff*, const EEnemyBuffCompatibility);
	FOverrideBuffSignature OverrideBuffMethod;

protected:
	friend class AEnemy;
	UFUNCTION(Category = "Buff Core")
		virtual void OnBuffBeginPlay(AEnemy* Enemy);
	UFUNCTION(Category = "Buff Core")
		virtual void OnBuffTick(AEnemy* Enemy, float DeltaTime);
	UFUNCTION(Category = "Buff Core")
		virtual void OnBuffEndPlay(AEnemy* Enemy, const EEnemyBuffEndReason Reason);
	DECLARE_DELEGATE_OneParam(FEnemyBeginPlaySignature, AEnemy*);
	FEnemyBeginPlaySignature EnemyBuffBeginPlayMethod;
	DECLARE_DELEGATE_TwoParams(FEnemyBuffTickSignature, AEnemy*, float);
	FEnemyBuffTickSignature EnemyBuffTickMethod;
	DECLARE_DELEGATE_TwoParams(FEnemyBuffEndPlaySignature, AEnemy*, const EEnemyBuffEndReason);
	FEnemyBuffEndPlaySignature EnemyBuffEndPlayMethod;
	// Set this tag to true causes destroyed at Enemy::Tick
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Life Cycle")
		bool bLifeCycleExpired = false;
	
public:
	UFUNCTION(BlueprintCallable, Category = "Identifier") void SetUniqueBuffName(FString NewName) { UniqueBuffName = NewName; }
	UFUNCTION(BlueprintCallable, Category = "Identifier") FString GetUniqueBuffName() const { return UniqueBuffName; }
	UFUNCTION(BlueprintCallable, Category = "Apply")
	virtual bool CanApplyToEnemy(AEnemy* Enemy) {
		if (CanApplyToEnemyMethod.IsBound())
			return CanApplyToEnemyMethod.Execute(Enemy);
		return true;
	}
	UFUNCTION(BlueprintCallable, Category = "Apply")
	virtual EEnemyBuffCompatibility IsCompatibleWith(UEnemyBuff* OtherBuff) {
		if (IsCompatibleWithMethod.IsBound())
			return IsCompatibleWithMethod.Execute(OtherBuff);
		if (UniqueBuffName == OtherBuff->UniqueBuffName)
			return EEnemyBuffCompatibility::OverrideOld;
		else
			return EEnemyBuffCompatibility::Compatible;
	}
	UFUNCTION(BlueprintCallable, Category = "Apply")
	virtual void OverrideBuff(UEnemyBuff* OtherBuff, EEnemyBuffCompatibility ConflictType) {
		OverrideBuffMethod.ExecuteIfBound(OtherBuff, ConflictType);
	}
};


UCLASS(Category = "Enemy Buff|Slow")
class LUAMACHINEPROJECT_API UEDecelerateBuff : public UEnemyBuff
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEDecelerateBuff(const FObjectInitializer& Initializer = FObjectInitializer::Get());

public:
	UPROPERTY(EditAnywhere, Category = "Enemy Buff|Slow") float SpeedMulLoss;
	UPROPERTY(EditAnywhere, Category = "Enemy Buff|Slow") float SpeedOffsetLoss;

public:
	// Assume all deceleration buff with the same unique buff name has a same value of property SpeedMulLoss
	virtual void OverrideBuff(UEnemyBuff* OtherBuff, EEnemyBuffCompatibility ConflictType) override;
};

UCLASS(Category = "Enemy Buff |Stun")
class LUAMACHINEPROJECT_API UEStunBuff :public UEnemyBuff {
	GENERATED_BODY()

public:
	UEStunBuff(const FObjectInitializer& Initializer = FObjectInitializer::Get());

public:
	virtual void OverrideBuff(UEnemyBuff* OtherBuff, EEnemyBuffCompatibility ConflictType) override;
};
