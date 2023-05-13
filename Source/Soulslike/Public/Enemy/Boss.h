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

protected:
	void ChooseAttack() override;

private:
	void Transform();
	void AttackRush();
	void AttackJump();
	void PlayMontageName(UAnimMontage* Montage);

	bool IsRush = false;
	bool IsJump = false;
	FVector AttackTargetLocation;

	UFUNCTION(BlueprintCallable)
	void TransformEnd();

	UFUNCTION(BlueprintCallable)
	void AttackRushEnd();

	UFUNCTION(BlueprintCallable)
	void AttackJumpEnd();

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	EBossPhase BossPhase = EBossPhase::EBP_Phase1;

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
