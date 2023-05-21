// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Insect.h"
#include "Characters/CharacterType.h"
#include "Boss.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossEngage, ABoss*, EngagedBoss);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossDefeat, ABoss*, DefeatedBoss);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBossGetHit, float, BossHealthPercent);

UCLASS()
class SOULSLIKE_API ABoss : public AInsect
{
	GENERATED_BODY()
	

public:
	ABoss();

	virtual void HandleDamage(float DamageAmount) override;

	FOnBossEngage OnBossEngage;
	FOnBossDefeat OnBossDefeat;
	FOnBossGetHit OnBossGetHit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	EBossPhase BossPhase = EBossPhase::EBP_Phase1;

	UFUNCTION()
	FName GetBossName();

protected:
	virtual void BeginPlay() override;
	virtual void ChaseTarget() override;
	void ChooseAttack() override;
	void Attack2() override;
	void SpawnRandom() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsFirstEngaged = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsRush = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsJump = false;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeapon* EquippedWeapon2;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeapon* EquippedWeapon3;

	UFUNCTION(BlueprintCallable)
	void SetWeapon2CollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	UFUNCTION(BlueprintCallable)
	void SetWeapon3CollisionEnabled(ECollisionEnabled::Type CollisionEnabled);


private:
	void Transform();
	void Engage();
	void AttackRush();
	void AttackJump();
	void PlayMontageName(UAnimMontage* Montage);
	void SpawnDefaultBossWeapon();
	FVector AttackTargetLocation;

	UFUNCTION(BlueprintCallable)
	void TransformEnd();

	UFUNCTION(BlueprintCallable)
	void AttackRushEnd();

	UFUNCTION(BlueprintCallable)
	void AttackJumpEnd();

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AWeapon> WeaponClass2;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AWeapon> WeaponClass3;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RushSpeed = 1200.f;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* TransformMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EngageMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* AttackRushMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* AttackJumpMontage;

	UPROPERTY(VisibleAnywhere)
	FName BossName = FName(TEXT("Golem"));
};
