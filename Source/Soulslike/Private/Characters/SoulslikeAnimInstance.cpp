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

	if (SoulslikeCharacter && SoulslikeCharacterMovement)
	{
		FVector Velocity = SoulslikeCharacterMovement->Velocity;
		GroundSpeed = UKismetMathLibrary::VSizeXY(Velocity);
		GroundDirection = CalculateDirection(Velocity, SoulslikeCharacter->GetActorRotation());
		IsFalling = SoulslikeCharacterMovement->IsFalling();
		CharacterState = SoulslikeCharacter->GetCharacterState();
		ActionState = SoulslikeCharacter->GetActionState();
		DeathPose = SoulslikeCharacter->GetDeathPose();

		// Aim
		//FRotator AimRotation = SoulslikeCharacter->GetBaseAimRotation();
		//FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Velocity);

		//MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
	}
}
