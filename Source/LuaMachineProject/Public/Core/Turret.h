// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LunePawnBase.h"
#include "CommonActors.h"
#include "AttackBehavior.h"
#include "Components/SphereComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS()
class LUAMACHINEPROJECT_API ATurret : public ALunePawnBase
{
	GENERATED_BODY()

public:
	ATurret(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UFUNCTION() virtual void BeginPlay() override;
public:
	UFUNCTION() virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY() int32 Price;
	UPROPERTY() int32 MoneyCost;

protected:
	UPROPERTY(EditAnywhere, Category = Damage) float Damage;
	UPROPERTY(VisibleAnywhere, Transient, Category = Damage) float DamageOffset;
	UPROPERTY(VisibleAnywhere, Transient, Category = Damage) float DamageMul;
	UPROPERTY(VisibleAnywhere, Transient, Category = Damage) float DamageAddon;
	UPROPERTY(VisibleAnywhere, Transient, Category = Damage) float DamageActual;

	UPROPERTY(EditAnywhere, Category = "Attack Range") float Range;
	UPROPERTY(VisibleAnywhere, Transient, Category = "Attack Range") float RangeMul;
	UPROPERTY(VisibleAnywhere, Transient, Category = "Attack Range") float RangeActual;

public:
	static FName GetStaticUniqueName() { return FName(TEXT("ATurret(ALuneActorBase(AActor))")); }
	virtual FName GetUniqueName() const override { return FName(TEXT("ATurret(ALuneActorBase(AActor))")); }

	UFUNCTION(BlueprintCallable)
		void SetPrice(int32 _price)
	{
		if (IsInitializationCompleted()) {
			UE_LOG(LuneProject, Error, TEXT("%s"), *UCommonActors::FormatInitCompleteVialationMessage(TEXT("Turret"), TEXT("Price")));
			return;
		}
		if (_price < 0) {
			UE_LOG(LuneProject, Error, TEXT("Turret::Price cannot be < 0 (the value you set is %d)."), _price);
			return;
		}
		Price = _price;
	}
	UFUNCTION(BlueprintCallable) int32 GetPrice() const { return Price; }
	UFUNCTION(BlueprintCallable) void SetMoneyCost(int32 _money) {
		if (_money < 0) {
			UE_LOG(LuneProject, Error, TEXT("Turret::MoneyCost cannot be < 0 (the value you set is %d)."), _money);
			return;
		}
		MoneyCost = _money;
	}
	UFUNCTION(BlueprintCallable) int32 GetMoneyCost() const { return MoneyCost; }


	UFUNCTION(BlueprintCallable) int32 GetDamage() const { return Damage; }
	UFUNCTION(BlueprintCallable) void SetDamage(float _damage) {
		if (_damage < 0) {
			UE_LOG(LuneProject, Error, TEXT("Turret::Damage cannot be < 0 (the value you set is %f)."), _damage);
			return;
		}
		Damage = _damage;
		RecalculateDamage();
	}
	UFUNCTION(BlueprintCallable) float GetDamageActual() {
		return DamageActual;
	}
	UFUNCTION(BlueprintCallable) void RecalculateDamage() {
		DamageActual = (Damage + DamageOffset)*DamageMul + DamageAddon;
	}
	UFUNCTION(BlueprintCallable) void AddDamageOffset(float offset) {
		DamageOffset += offset;
		RecalculateDamage();
	}
	UFUNCTION(BlueprintCallable) void AddDamageMul(float mul) {
		DamageMul += mul;
		RecalculateDamage();
	}
	UFUNCTION(BlueprintCallable) float GetDamageOffset() const { return DamageOffset; }
	UFUNCTION(BlueprintCallable) float GetDamageMul() const { return DamageMul; }
	UFUNCTION(BlueprintCallable) void ResetDamage() {
		DamageOffset = 0;
		DamageMul = 1;
		DamageActual = Damage;
	}

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class USphereComponent* AttackRange;
	UFUNCTION(BlueprintCallable, Category = "Attack Range") float GetRange() const { return Range; }
	UFUNCTION(BlueprintCallable, Category = "Attack Range") void SetRange(float _range) { Range = _range; RecalculateRange(); }
	UFUNCTION(BlueprintCallable, Category = "Attack Range") void RecalculateRange() { RangeActual = Range*RangeMul; }
	UFUNCTION(BlueprintCallable, Category = "Attack Range") void ResetRange() { RangeMul = 1; RangeActual = Range; SetupRange();}
	UFUNCTION(BlueprintCallable, Category = "Attack Range") void SetupRange() {
		AttackRange->SetSphereRadius(RangeActual);
	}
	UFUNCTION(BlueprintCallable, Category = "Attack Range") float GetRangeActual() const { return RangeActual; }
	UFUNCTION(BlueprintCallable, Category = "Attack Range") void AddRangeMul(float _mul) {
		RangeMul += _mul; RecalculateRange(); SetupRange();
	}
	UFUNCTION(BlueprintCallable, Category = "Attack Range") void OnAttackRangeOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY() TArray<UAttackBehavior*> Attackers;
	void ReadAttackers();

	UPROPERTY() TArray<class UTurretBuff*> ActiveBuffs;
public:
	void AddBuff(UTurretBuff* buff) {
		ActiveBuffs.Add(buff);
	}
	void RemoveBuff(UTurretBuff* buff) {
		ActiveBuffs.Remove(buff);
	}

public:
	virtual class ABullet* GenerateBullet(class Enemy* Target);
	TSubclassOf<class ABullet> BulletPrototype;
};
