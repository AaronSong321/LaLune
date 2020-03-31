// Fill out your copyright notice in the Description page of Project Settings.

#include "LuneHud.h"
#include "UObject/ConstructorHelpers.h"

#include "Core/Widgets/ITurretPanel.h"


ALuneHud::ALuneHud(const FObjectInitializer& ObjectInitializer) :AHUD(ObjectInitializer){
	//static ConstructorHelpers::FClassFinder<UITurretPanel> TurretPanelVisual(TEXT("WidgetBlueprint'/Game/Widgets/TurretPanelBp.TurretPanelBp'"));
	//UClass* MyWidgetClass = TurretPanelVisual.Class;
	//TurretPanel = NewObject<UITurretPanel>(nullptr, MyWidgetClass);
	//TurretPanel->AddToViewport();
}

void ALuneHud::BeginPlay() {
	AHUD::BeginPlay();


}


