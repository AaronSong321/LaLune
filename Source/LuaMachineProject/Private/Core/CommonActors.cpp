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