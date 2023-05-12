// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "CharacterType.h"
#include "Interfaces/PickupInterface.h"
#include "SoulslikeCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;
class USoulslikeOverlay;
class ASoul;
class ATreasure;
class UTargetSystemComponent;


UCLASS()
class SOULSLIKE_API ASoulslikeCharacter : public ABaseCharacter, public IPickupInterface
{
	GENERATED_BODY()

public:
	ASoulslikeCharacter();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	// Callbacks for Input

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* SoulslikeContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* EKeyAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* Attack1Action;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DodgeAction;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* LockOnAction;

	void Move(const FInputActionValue& Value);
	void MoveEnd(const  FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EKeyPressed();

	// Combat

	void Dodge();
	void LockOn();
	void EquipWeapon(AWeapon* Weapon);
	virtual void Attack1() override;
	virtual void AttackEnd() override;
	virtual bool CanAttack() override;
	virtual void DodgeEnd() override;
	virtual void DodgeInvincibleEnd() override;

	void PlayEquipMontage(FName SectionName);
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Enarm();
	void FaceTarget(FVector TargetVector);
	virtual void Die_Implementation() override;

	UFUNCTION()
	void OnTargetOn(AActor* TargetActor);

	UFUNCTION()
	void OnTargetOff(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();

	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();

	UFUNCTION(BlueprintCallable)
	void FinishEquipping();

	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void SetOverlappingItem(AItem* Item) override;
	virtual void AddSouls(ASoul* Soul) override;
	virtual void AddGolds(ATreasure* Gold) override;

	UPROPERTY(EditAnywhere)
	float TargetMinimumDistance = 2000.f;

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }

private:
	void SetHUDHealth();
	void InitializeSoulslikeOverlay();
	void SetDodgeDirectionForward();
	bool IsUnoccupied();
	bool IsDead();
	bool HasEnoughStamina();
	void ChangeControllerRotationYaw(bool IsUsing);

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	// Character Components

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UTargetSystemComponent* TargetSystem;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY()
	USoulslikeOverlay* SoulslikeOverlay;

	UPROPERTY()
	FVector DodgeDirection;
};
