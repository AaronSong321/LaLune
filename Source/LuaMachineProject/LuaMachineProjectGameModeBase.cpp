// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaMachineProjectGameModeBase.h"
#include "Core/LuneCharacter.h"


DEFINE_LOG_CATEGORY_STATIC(LogProject, Log, All)

ALuaMachineProjectGameModeBase::ALuaMachineProjectGameModeBase()
{
	DefaultPawnClass = ALuneCharacter::StaticClass();

}

void ALuaMachineProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void ALuaMachineProjectGameModeBase::TestCreateCollide()
{

}

