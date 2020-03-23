// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Tickable.h"
#include "LuneObjectBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class LUAMACHINEPROJECT_API ULuneObjectBase : public UObject, public FTickableGameObject
{
	GENERATED_BODY()


protected:
	UPROPERTY()
	uint8 bCanEverTick : 1;
	
private:
	uint8 bInitializationCompleted : 1;

public:
	ULuneObjectBase();

	UFUNCTION(BlueprintCallable)
	static FName GetStaticUniqueName() { return FName(TEXT("ULuneObjectBase(UObject)")); }
	UFUNCTION(BlueprintCallable)
	virtual FName GetUniqueName() const { return FName(TEXT("ULuneObjectBase(UObject)")); }
protected:
	UFUNCTION(BlueprintCallable) 
	uint8 IsInitializationCompleted() { return bInitializationCompleted; }
	UFUNCTION(BlueprintCallable)
	void LockObject() { bInitializationCompleted = 1; }
	
public:
	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) {}
	virtual bool IsTickable() const override { return GIsRunning && (bool)bCanEverTick; }
	virtual TStatId GetStatId() const override { return UObject::GetStatID(); }
	// End FTickableGameObject Interface.
	
};
