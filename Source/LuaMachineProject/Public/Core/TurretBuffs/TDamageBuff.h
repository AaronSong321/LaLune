// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core/TurretBuff.h"
#include "TDamageBuff.generated.h"

class ATurret;
class ABullet;


/**
 * 
 */
UCLASS(Category = "Turret Buff|Damage Buff")
class LUAMACHINEPROJECT_API UTDamageBuff : public UTurretBuff
{
	GENERATED_BODY()

public:
	UTDamageBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Damage Buff|Damage")
	float Damage;
	UPROPERTY(EditAnywhere, Transient, Category = "Turret Buff|Damage Buff|Damage") float DamageOffset;
	UPROPERTY(EditAnywhere, Transient, Category = "Turret Buff|Damage Buff|Damage") float DamageMul;
	UPROPERTY(EditAnywhere, Transient, Category = "Turret Buff|Damage Buff|Damage") float DamageAddon;
	UPROPERTY(VisibleAnywhere, Transient, Category = "Turret Buff|Damage Buff|Damage") float DamageActual;
public:
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") float GetDamage() const { return Damage; }
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") void SetDamage(float _damage) {
		if (_damage < 0) {
			UE_LOG(LuneProject, Error, TEXT("Turret::Damage cannot be < 0 (the value you set is %f)."), _damage);
			return;
		}
		Damage = _damage;
		CalcDamage();
	}
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") float GetDamageActual() {
		return DamageActual;
	}
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") void CalcDamage() {
		DamageActual = (Damage + DamageOffset)*DamageMul + DamageAddon;
	}
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") void AddDamageOffset(float offset) {
		DamageOffset += offset;
		CalcDamage();
	}
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") void AddDamageMul(float mul) {
		DamageMul += mul;
		CalcDamage();
	}
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") float GetDamageOffset() const { return DamageOffset; }
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") float GetDamageMul() const { return DamageMul; }
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Damage Buff|Damage") void ResetDamage() {
		DamageOffset = 0;
		DamageMul = 1;
		DamageActual = Damage;
	}


public:
	virtual bool CanApplyToTurret(ATurret* Turret) const override { return true; }

private:
	UFUNCTION(BlueprintCallable, Category = "Turret Buff|Apply")
	void ThisRetrofitBullet(ABullet* Bullet);

};

UCLASS(Category = "Turret Buff|Decelerate Buff")
class LUAMACHINEPROJECT_API UTDecelerateBuff : public UTurretBuff
{
	GENERATED_BODY()

public:
	UTDecelerateBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Decelerate Buff")
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Decelerate Buff")
		float SpeedOffsetLoss;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Decelerate Buff")
		float SpeedMulLoss;

public:
	virtual bool CanApplyToTurret(ATurret* Turret) const override { return true; }

private:
	void ThisRetrofitBullet(ABullet* Bullet);

};

UCLASS(Category = "Turret Buff|Stun Buff")
class LUAMACHINEPROJECT_API UTStunBuff : public UTurretBuff
{
	GENERATED_BODY()

public:
	UTStunBuff(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Stun Buff")
		float Duration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret Buff|Stun Buff")
		float Possibility;
	
private:
	void ThisRetrofitBullet(ABullet* Bullet);

};
