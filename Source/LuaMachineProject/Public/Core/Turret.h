// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LunePawnBase.h"
#include "CommonActors.h"
#include "Components/SphereComponent.h"
#include "Turret.generated.h"


class UTurretBuff;
class UAttackBehavior;
class ABullet;
class AEnemy;
struct FPropertyChangeEvent;

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
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UPROPERTY() int32 Price;
	UPROPERTY() int32 MoneyCost;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Range") float Range;
	UPROPERTY(EditAnywhere, Transient, Category = "Attack Range") float RangeMul;
	UPROPERTY(VisibleAnywhere, Transient, Category = "Attack Range") float RangeActual;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Attribute") float BulletSpeed;

protected:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perk Category") 
		EPerkName PerkCategory;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perk Category") 
		EPerkName PerkCategoryAddon;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Perk Category")
		EPerkName PerkCategoryActual;
public:
	//UFUNCTION(BlueprintCallable, Category = "Perk Category") 
	FORCEINLINE void AddPerkCategory(EPerkName NewCategory) {
		PerkCategoryAddon = PerkCategoryAddon | NewCategory;
	}
	//UFUNCTION(BlueprintCallable, Category = "Perk Category") 
	FORCEINLINE void RemovePerkCategory(EPerkName DroppedCategory) {
		PerkCategoryAddon = PerkCategoryAddon & (EPerkName)(!(int32)DroppedCategory);
	}
	FORCEINLINE void CalcPerkCategory() {
		PerkCategoryActual = PerkCategory | PerkCategoryAddon;
	}

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret Level") uint8 Level;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret Level") uint8 MaxLevel;


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

protected:
	// Determine what to do when an enemy is in range. The default behavior is to add the enemy to the WatchList.
	// This function is protected only to be override in blueprint and should not be called externally.
	UFUNCTION(Category = "Enemy Detection")
	virtual void OnAttackRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// This function is protected only to be override in blueprint and should not be called externally.
	UFUNCTION(Category = "Enemy Detection")
	virtual void OnAttackRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Determine whether this turret can attack this enemy. The default behavior is to see the ground-air value of turret and enemy.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Detection")
		TArray<AEnemy*> WatchList;
	// This function is protected only to be override in blueprint and should not be called externally.
	UFUNCTION(Category = "Enemy Detection")
		virtual void OnWatchedEnemyKilled(AEnemy* Enemy, ATurret* TurretInstigator, const EEnemyDieReason Reason);
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Enemy Detection")
		AEnemy* AimingTarget;
	// Decide which target to attack.
	// This function is public because there may be taunt ability.
	UFUNCTION(Category = "Enemy Detection")
		virtual void RefreshTarget();
	UFUNCTION(BlueprintCallable, Category = "Enemy Detection")
	virtual bool CanAttackEnemy(AEnemy* Enemy) const;
	UPROPERTY(EditAnywhere, Category = "Enemy Detection")
	EGroundAirValue GroundAirAbility;
	UPROPERTY() TArray<UAttackBehavior*> Attackers;
	void ReadAttackers();

public:
	// Buff list of ATurret is public for other classes to iterate. Use AddBuff, RemoveBuff to add or remove for common usage
	UPROPERTY(EditAnywhere, Category = "Buff")
		TArray<UTurretBuff*> ActiveBuffs;
	UFUNCTION(BlueprintCallable, Category = "Buff")
		void AddBuff(UTurretBuff* Buff);
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void RemoveBuff(UTurretBuff* Buff) {
		ActiveBuffs.Remove(Buff);
	}

public:
	// Agility means how fast this turret attacks. The canonical agility is 100, means the turret attacks once per second, and 200 agility means the turret attacks twice per second. 50 agility attacks once per two seconds.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		float Agility;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		float AgilityOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		float AgilityMul;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", Transient)
		float AgilityActual;
	// AttackWeek = 100 / Agility
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", Transient)
		float AttackWeek;
	// The percentage of attack point of an attack week. 0.3 means the turret aims for 0.3*AttackWeek before attacking.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		float AttackPointPercentage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", Transient)
		float AttackPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack", Transient)
		float AttackPhase;
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void SetAgility(float NewAgility) {
		Agility = NewAgility;
		RecalculateAgility();
	}
	UFUNCTION(BlueprintCallable, Category = "Attack")
	void RecalculateAgility() {
		AgilityActual = (Agility + AgilityOffset)*AgilityMul;
		AttackWeek = 100 / AgilityActual;
		AttackPoint = AttackWeek * AttackPointPercentage;
	}
protected:
	UFUNCTION(BlueprintCallable, Category = "Attack")
		virtual void TickAttack(float DeltaTime);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
		bool AttackFired;

public:
	UFUNCTION(BlueprintCallable, Category = "Attack")
	virtual ABullet* GenerateBullet(AEnemy* Target);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bullet Instantiation")
	TSubclassOf<ABullet> BulletPrototype;
};
