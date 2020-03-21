// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LuneObjectBase.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class LUAMACHINEPROJECT_API ULuneObjectBase : public UObject
{
	GENERATED_BODY()
	
private:
	uint8 bIntializationCompleted : 1;

public:
	ULuneObjectBase() { bIntializationCompleted = 0; }

	UFUNCTION(BlueprintCallable)
	static FName GetStaticUniqueName() { return FName(TEXT("ULuneObjectBase(UObject)")); }
	UFUNCTION(BlueprintCallable)
	virtual FName GetUniqueName() const { return FName(TEXT("ULuneObjectBase(UObject)")); }
protected:
	UFUNCTION(BlueprintCallable) 
	uint8 IsInitializationCompleted() { return bIntializationCompleted; }
	UFUNCTION(BlueprintCallable)
	void LockObject() { bIntializationCompleted = 1; }
	
	
};
