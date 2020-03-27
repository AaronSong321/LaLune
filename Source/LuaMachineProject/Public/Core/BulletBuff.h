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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
	uint8 bUseDamage : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Owner")
	ABullet* BuffOwner;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bullet Buff")
	uint8 bAddEnemyBuff : 1;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage")
	float Damage;
public:
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SetUseDamage(uint8 UseDamage) { bUseDamage = UseDamage; }
	UFUNCTION(BlueprintCallable, Category = "Damage")
	uint8 GetUseDmaage() const {
		return bUseDamage;
	}
	UFUNCTION(BlueprintCallable, Category = "Owner")
	void SetBuffOwner(ABullet* NewBuffOwner) { BuffOwner = NewBuffOwner; }
	UFUNCTION(BlueprintCallable, Category = "Owner")
	ABullet* GetBuffOwner() const { return BuffOwner; }
	UFUNCTION(BlueprintCallable, Category = "Bullet Buff")
	void SetAddEnemyBuff(uint8 AddEnemyBuff) { bAddEnemyBuff = AddEnemyBuff; }
	UFUNCTION(BlueprintCallable, Category = "Bullet Buff")
	uint8 GetAddEnemyBuff() const { return bAddEnemyBuff; }
	UFUNCTION(BlueprintCallable, Category = "Damage")
	void SetDamage(float NewDamage) { Damage = NewDamage; }
	UFUNCTION(BlueprintCallable, Category = "Damage")
	float GetDamage() const { return Damage; }

public:
	DECLARE_DELEGATE_TwoParams(FOnHitEnemySignature, UBulletBuff*, AEnemy*);
	// Define this behavior as a delegate rather than method so that we don't have to create an ad hoc class for every kind of bullet buff
	FOnHitEnemySignature OnBulletHitEnemy;
		
	
};
