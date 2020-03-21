// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "LuneCharacter.generated.h"


UCLASS(Config = Game)
class LUAMACHINEPROJECT_API ALuneCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ALuneCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* PerspectiveCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class USceneComponent* SceneComponent;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	uint8 bIntializationCompleted : 1;

public:
	UFUNCTION(BlueprintCallable, Category = Identity)
		static FName GetStaticUniqueName() { return FName(TEXT("ALuneCharacter(ACharacter)")); }
	UFUNCTION(BlueprintCallable, Category = Identity)
		virtual FName GetUniqueName() const { return FName(TEXT("ALuneCharacter(ACharacter)")); }
protected:
	UFUNCTION(BlueprintCallable, Category = Initialization)
		uint8 IsInitializationCompleted() { return bIntializationCompleted; }
	UFUNCTION(BlueprintCallable, Category = Initialization)
		void LockObject() { bIntializationCompleted = 1; }

public:
	UPROPERTY(EditAnywhere, Category = Camera)
		FQuat CameraDirection;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override {
		FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
		if ((PropertyName == GET_MEMBER_NAME_CHECKED(ALuneCharacter, CameraDirection))) {
			PerspectiveCamera->SetRelativeRotation(CameraDirection);
		}
	}
#endif

	UPROPERTY(EditAnywhere, Config, Category = Camera/*, Const*/)
	float CameraYawRad = 70.f * PI / 180.f;
	UPROPERTY(EditAnywhere, Config, Category = Camera/*, Const*/)
	float CameraDefaultHeight = 1000.f;
	UPROPERTY(VisibleAnywhere, Transient, Category = Camera)
	float CameraYawSin; 
	UPROPERTY(VisibleAnywhere, Transient, Category = Camera)
	float CameraYawCos;
	UPROPERTY(VisibleAnywhere, Transient, Category = Camera)
	FVector ForwardDirection;
	UPROPERTY(VisibleAnywhere, Transient)
		FVector SpawnLocation;
private:
	void CalcCameraConstants();

protected:
	UPROPERTY(EditAnywhere, Category = Camera) float CameraMoveUpSpeed;
	UPROPERTY(EditAnywhere, Category = Camera) float CameraMoveLeftSpeed;
	UPROPERTY(EditAnywhere, Category = Camera) float CameraZoomInSpeed;
	UPROPERTY(EditAnywhere, Category = Camera) float CameraZoomOutSpeed;
	UPROPERTY(EditAnywhere, Category = Health) float RechargeSpeed;

private:
	//FVector
	uint8 Recharging : 1;

	void MoveUp(float Scale);
	void BeginRecharge();
	void EndRecharge();
	void ResetCamera();
public:
	void Translate(const FVector& Distance);
	
};
