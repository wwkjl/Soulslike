// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterType.h"
#include "SoulslikeAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_API USoulslikeAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	class ASoulslikeCharacter* SoulslikeCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	class UCharacterMovementComponent* SoulslikeCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Movement")
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	ECharacterState CharacterState;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EActionState ActionState;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	TEnumAsByte<EDeathPose> DeathPose;
};
