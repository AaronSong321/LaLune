// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaMachineProjectGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

#include "Core/LuneCharacter.h"
#include "Core/LuneHud.h"


DEFINE_LOG_CATEGORY_STATIC(LogProject, Log, All)

ALuaMachineProjectGameModeBase::ALuaMachineProjectGameModeBase()
{
	DefaultPawnClass = ALuneCharacter::StaticClass();
	//HUDClass = ALuneHud::StaticClass();
	static ConstructorHelpers::FClassFinder<ALuneHud> HudClass(TEXT("Blueprint'/Game/CoreObjects/LuneHudVisual.LuneHudVisual_C'"));
	HUDClass = HudClass.Class;
}

void ALuaMachineProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

void ALuaMachineProjectGameModeBase::TestCreateCollide()
{

}

