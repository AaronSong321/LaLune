// Fill out your copyright notice in the Description page of Project Settings.

#include "BulletBuff.h"


// Sets default values for this component's properties
UBulletBuff::UBulletBuff()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBulletBuff::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBulletBuff::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UBulletBuff::EndPlay(const EEndPlayReason::Type Reason) {
	Super::EndPlay(Reason);
	OnBulletHitEnemy.Unbind();
}

