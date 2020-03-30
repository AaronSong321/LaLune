// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonActors.h"
#include "Engine.h"

#define InitializationCompleteVialationFormatTemplate TEXT("Object \"%s\" is already intialized, and you cannot change property \"%s\"")


UCommonActors::UCommonActors()
{
}

UCommonActors::~UCommonActors()
{
}

DEFINE_LOG_CATEGORY(LuneProject)
//const TCHAR* UCommonActors::InitializationCompleteVialationFormatTemplate = TEXT("Object \"%s\" is already intialized, and you cannot change property \"%s\"");

FString UCommonActors::FormatInitCompleteVialationMessage(FString ClassName, FString PropertyName)
{
	return FString::Printf(InitializationCompleteVialationFormatTemplate, *ClassName, *PropertyName);
}

bool operator& (const EGroundAirValue left, const EGroundAirValue right) {
	return ((uint8)left & (uint8)right) != 0;
}

EPerkName operator&(const EPerkName left, const EPerkName right) {
	return (EPerkName)((int32)left & (int32)right);
}

EPerkName operator|(const EPerkName left, const EPerkName right) {
	return (EPerkName)((int32)left | (int32)right);
}
