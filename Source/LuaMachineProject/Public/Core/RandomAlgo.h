// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RandomAlgo.generated.h"

/**
 * 
 */
// Under construction, DO NOT use!
UCLASS()
class LUAMACHINEPROJECT_API URandomAlgo : public UObject
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Possibility;
	
public:
	FORCEINLINE void SetPossibility(float NewPossibility) { Possibility = NewPossibility; }

	
};
