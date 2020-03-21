// Fill out your copyright notice in the Description page of Project Settings.

#include "LuneCharacter.h"
#include "CommonActors.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/InputSettings.h"
#include "Engine/World.h"

// Sets default values
ALuneCharacter::ALuneCharacter() : CameraMoveUpSpeed(500), CameraMoveLeftSpeed(500), CameraZoomInSpeed(1500), CameraZoomOutSpeed(1000), Recharging(0), RechargeSpeed(50)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// Make the scene component the root component
	RootComponent = SceneComponent;

	// Setup camera defaults
	PerspectiveCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	PerspectiveCamera->FieldOfView = 90.0f;
	PerspectiveCamera->bConstrainAspectRatio = true;
	PerspectiveCamera->AspectRatio = 1.777778f;
	PerspectiveCamera->PostProcessBlendWeight = 1.0f;
	PerspectiveCamera->SetupAttachment(SceneComponent);

	CalcCameraConstants();
	SetActorLocation(SpawnLocation);
	PerspectiveCamera->SetRelativeRotation(FQuat(FVector(0, 1, 0), CameraYawRad));
}

void ALuneCharacter::CalcCameraConstants() {
	//FMath::SinCos(&CameraYawSin, &CameraYawCos, FMath::RadiansToDegrees(CameraYawRad));
	CameraYawSin = FMath::Sin(FMath::RadiansToDegrees(CameraYawRad));
	CameraYawCos = FMath::Cos(FMath::RadiansToDegrees(CameraYawRad));
	//ForwardDirection.X = CameraYawSin;
	//ForwardDirection.Z = -CameraYawCos;
	ForwardDirection.X = 1;
	SpawnLocation = FVector(-CameraDefaultHeight * CameraYawSin/2, 0, CameraDefaultHeight);
}

// Called when the game starts or when spawned
void ALuneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALuneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Recharging) {
		UE_LOG(LuneProject, Log, TEXT("Recharging: health point + %f"), DeltaTime*RechargeSpeed);
	}
}


// Called to bind functionality to input
void ALuneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Modify key bindings in C++
	const UInputSettings* InputSettings = GetDefault<UInputSettings>();
	UInputSettings* ModifyInputSettings = (UInputSettings*)InputSettings;
	//ModifyInputSettings->AxisMappings.Empty();
	ModifyInputSettings->AddAxisMapping(FInputAxisKeyMapping(FName("CameraUp"), FKey(FName(TEXT("W"))), 1.f));
	ModifyInputSettings->AddAxisMapping(FInputAxisKeyMapping(FName("CameraUp"), FKey(FName(TEXT("S"))), -1.f));
	ModifyInputSettings->AddAxisMapping(FInputAxisKeyMapping(FName("CameraRight"), FKey(FName(TEXT("D"))), 1.f));
	ModifyInputSettings->AddAxisMapping(FInputAxisKeyMapping(FName("CameraRight"), FKey(FName(TEXT("A"))), -1.f));
	ModifyInputSettings->AddActionMapping(FInputActionKeyMapping(FName("ZoomIn"), FKey(FName(TEXT("MouseScrollUp")))));
	ModifyInputSettings->AddActionMapping(FInputActionKeyMapping(FName("ZoomOut"), FKey(FName(TEXT("MouseScrollDown")))));
	//ModifyInputSettings->ActionMappings.Empty();
	ModifyInputSettings->AddActionMapping(FInputActionKeyMapping(FName("Recharge"), FKey(FName(TEXT("R")))));
	ModifyInputSettings->AddActionMapping(FInputActionKeyMapping(FName("CameraReset"), FKey(FName(TEXT("T"))), false, false, true, false));

	// Uncomment this when axis key mapping is not the same as you wish
	//TArray<FInputAxisKeyMapping>& axisMapping = ModifyInputSettings->AxisMappings;
	//for (int32 i = 0, size = axisMapping.Num(); i < size; ++i) {
	//	const auto& axis = axisMapping[i];
	//	UE_LOG(LuneProject, Log, TEXT("%s %s %f"), *axis.AxisName.ToString(), *axis.Key.ToString(), axis.Scale);
	//}

	PlayerInputComponent->BindAxis("CameraUp", this, &ALuneCharacter::MoveUp);
	PlayerInputComponent->BindAxis("CameraRight", this, &ALuneCharacter::MoveRight);
	PlayerInputComponent->BindAction("Recharge", EInputEvent::IE_Pressed, this, &ALuneCharacter::BeginRecharge);
	PlayerInputComponent->BindAction("Recharge", EInputEvent::IE_Released, this, &ALuneCharacter::EndRecharge);
	PlayerInputComponent->BindAction("CameraReset", EInputEvent::IE_Pressed, this, &ALuneCharacter::ResetCamera);
	PlayerInputComponent->BindAction("ZoomIn", IE_Pressed, this, &ALuneCharacter::ZoomIn);
	PlayerInputComponent->BindAction("ZoomOut", IE_Pressed, this, &ALuneCharacter::ZoomOut);
}

void ALuneCharacter::MoveUp(float Scale) {
	if (Scale != 0.f) {
		const float moveDistance = CameraMoveUpSpeed * Scale * GetWorld()->GetDeltaSeconds();
		const FVector move = ForwardDirection * moveDistance;
		Translate(move);
	}
}

void ALuneCharacter::MoveRight(float Scale) {
	static const FVector RightDirection(0, 1, 0);
	if (Scale != 0.f) {
		const float moveDistance = CameraMoveLeftSpeed * Scale * GetWorld()->GetDeltaSeconds();
		const FVector move = RightDirection * moveDistance;
		Translate(move);
	}
}

void ALuneCharacter::ZoomIn() {
	Translate(FVector(CameraYawSin, 0, -1)*CameraZoomInSpeed*GetWorld()->GetDeltaSeconds());
}

void ALuneCharacter::ZoomOut() {
	Translate(FVector(-CameraYawSin, 0, 1)*CameraZoomOutSpeed*GetWorld()->GetDeltaSeconds());
}

void ALuneCharacter::BeginRecharge() {
	Recharging = 1;
}

void ALuneCharacter::EndRecharge() {
	Recharging = 0;
}

void ALuneCharacter::ResetCamera() {
	SetActorLocation(SpawnLocation);
	PerspectiveCamera->SetRelativeRotation(FQuat(FVector(0, 1, 0), CameraYawRad));
	UE_LOG(LuneProject, Log, TEXT("Reset camera"))
}

void ALuneCharacter::Translate(const FVector& Distance) {
	FVector t = GetActorLocation();
	SetActorLocation(t + Distance);
}
