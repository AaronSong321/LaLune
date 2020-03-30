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

UENUM()
enum class EGroundAirValue : uint8 {
	None = 0,
	Ground = 1,
	Air = 2,
	GroundAir = 3
};
bool operator& (const EGroundAirValue left, const EGroundAirValue right);

UENUM()
enum class EEnemyDieReason :uint8 {
	ZeroHealth = 0,
	ArriveAtDestination,
	InstantKill
};

UENUM()
enum class EEnemyBuffEndReason :uint8 {
	TimesUp = 0,
	EnemyDie,
	Discard
};

UENUM()
enum class EEnemyBuffCompatibility :uint8 {
	Compatible = 0,
	DiscardOld,
	DiscardThis,
	OverrideOld
};

//UENUM()
enum class EPerkName :int32 {
	Dummy = 0,
	Soilder = 1,
	Bomber = 1 << 1,
	Arsonist = 1 << 2,
	Electron = 1 << 3,
	Couch = 1 << 4
};
EPerkName operator&(const EPerkName left, const EPerkName right);
EPerkName operator|(const EPerkName left, const EPerkName right);

#define LOGFL() UE_LOG(LuneProject, Log, TEXT("[%s %d]"), __FUNCTIONW__, __LINE__)
#define ERRORFL(Message) UE_LOG(LuneProject, Error, TEXT("[%s %d]: %s"), __FUNCTIONW__, __LINE__, Message)

