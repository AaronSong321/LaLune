// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "LunePawnBase.generated.h"

UCLASS()
class LUAMACHINEPROJECT_API ALunePawnBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALunePawnBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	uint8 bIntializationCompleted : 1;

protected:
	UFUNCTION(BlueprintCallable)
		uint8 IsInitializationCompleted() { return bIntializationCompleted; }
	UFUNCTION(BlueprintCallable)
		void LockObject() { bIntializationCompleted = 1; }
	
};
