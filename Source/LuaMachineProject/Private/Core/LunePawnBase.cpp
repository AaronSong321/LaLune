// Fill out your copyright notice in the Description page of Project Settings.

#include "LunePawnBase.h"


// Sets default values
ALunePawnBase::ALunePawnBase() : bIntializationCompleted(0)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALunePawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALunePawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALunePawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

