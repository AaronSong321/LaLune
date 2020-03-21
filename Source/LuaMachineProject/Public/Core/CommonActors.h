// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommonActors.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API UCommonActors : public UObject
{
	GENERATED_BODY()


public:
	UCommonActors();
	~UCommonActors();

	//static const TCHAR* InitializationCompleteVialationFormatTemplate;
	UFUNCTION(BlueprintCallable)
	static FString FormatInitCompleteVialationMessage(FString ClassName, FString PropertyName);
};

DECLARE_LOG_CATEGORY_EXTERN(LuneProject, Verbose, All)

