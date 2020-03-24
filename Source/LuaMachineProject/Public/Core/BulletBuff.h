// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BulletBuff.generated.h"

class ABullet;
class AEnemy;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LUAMACHINEPROJECT_API UBulletBuff : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBulletBuff();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

public:
	uint8 bUseDamage : 1;
	ABullet* BuffOwner;
	uint8 bAddEnemyBuff : 1;
	float Damage;
	
public:
	DECLARE_DELEGATE_TwoParams(FOnHitEnemySignature, UBulletBuff*, AEnemy*);
	// Define this behavior as a delegate rather than method so that we don't have to create an ad hoc class for every kind of bullet buff
	FOnHitEnemySignature OnBulletHitEnemy;
		
	
};
