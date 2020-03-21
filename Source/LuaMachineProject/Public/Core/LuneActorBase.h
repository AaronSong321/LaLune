// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LuneActorBase.generated.h"

UCLASS(Abstract)
class LUAMACHINEPROJECT_API ALuneActorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuneActorBase();

	UFUNCTION(BlueprintCallable)
	static FName GetStaticUniqueName() { return FName(TEXT("ALuneActorBase(AActor)")); }
	UFUNCTION(BlueprintCallable)
	virtual FName GetUniqueName() const { return FName(TEXT("ULuneObjectBase(UObject)")); }
private:
	uint8 bIntializationCompleted : 1;

protected:
	UFUNCTION(BlueprintCallable)
	uint8 IsInitializationCompleted() { return bIntializationCompleted; }
	UFUNCTION(BlueprintCallable)
	void LockObject() { bIntializationCompleted = 1; }
	
};
