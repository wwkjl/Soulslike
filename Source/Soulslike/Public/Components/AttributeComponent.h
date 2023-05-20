// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SOULSLIKE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttributeComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Heal(float Point);
	void ReceiveDamage(float Damage);
	void UseStamina(float StaminaCost);
	void RegenStamina(float DeltaTime);
	bool IsAlive();
	bool IsLessHealthRatio(float Ratio);
	void AddSouls(int32 NumberOfSouls);
	void AddGolds(int32 AmountOfGolds);
	void AddPotion();
	void UsePotion();
	bool HasPotion();

	float GetHealthPercent();
	float GetStaminaPercent();
	FORCEINLINE int32 GetGolds() const { return Golds; }
	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE int32 GetPotions() const { return Potions;  }
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetDodgeCost() const { return DodgeCost; }
	FORCEINLINE float GetAttackCost() const { return AttackCost; }

private:
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Health;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float Stamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxStamina;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Golds;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Souls;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	int32 Potions;
	
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float DodgeCost = 12.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float AttackCost = 10.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float PotionHealPoint = 40.f;

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float StaminaRegenRate = 15.f;
};
