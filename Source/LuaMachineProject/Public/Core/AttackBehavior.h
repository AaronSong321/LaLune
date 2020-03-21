// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuneObjectBase.h"
#include "AttackBehavior.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API UAttackBehavior : public ULuneObjectBase
{
	GENERATED_BODY()
	
public:
	//UFUNCTION(BlueprintCallable)
	static FName GetStaticUniqueName() { return FName(TEXT("UAttackBehavior(ULuneObjectBase(UObject))")); }
	//UFUNCTION(BlueprintCallable)
	virtual FName GetUniqueName() const override { return FName(*AttackBehaviorName); }

private:
	UPROPERTY() FString AttackBehaviorName;

public:
	UFUNCTION(BlueprintCallable) void SetAttackBehaviorName(FString name) { AttackBehaviorName = name; }

};
