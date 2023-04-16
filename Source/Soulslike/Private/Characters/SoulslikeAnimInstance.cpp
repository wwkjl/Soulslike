// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SoulslikeAnimInstance.h"
#include "Characters/SoulslikeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USoulslikeAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SoulslikeCharacter = Cast<ASoulslikeCharacter>(TryGetPawnOwner());
	if (SoulslikeCharacter)
	{
		SoulslikeCharacterMovement = SoulslikeCharacter->GetCharacterMovement();
	}
}

void USoulslikeAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (SoulslikeCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(SoulslikeCharacterMovement->Velocity);
		IsFalling = SoulslikeCharacterMovement->IsFalling();
		CharacterState = SoulslikeCharacter->GetCharacterState();
	}
}
