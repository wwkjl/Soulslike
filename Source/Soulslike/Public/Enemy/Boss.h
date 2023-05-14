// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Insect.h"
#include "Characters/CharacterType.h"
#include "Boss.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_API ABoss : public AInsect
{
	GENERATED_BODY()
	

public:
	ABoss();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	EBossPhase BossPhase = EBossPhase::EBP_Phase1;

protected:
	virtual void BeginPlay() override;
	void ChooseAttack() override;
	void Attack2() override;

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
};
