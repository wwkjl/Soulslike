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

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void EKeyPressed();

	// Combat

	void Dodge();
	void EquipWeapon(AWeapon* Weapon);
	virtual void Attack1() override;
	virtual void AttackEnd() override;
	virtual bool CanAttack() override;
	virtual void DodgeEnd() override;

	void PlayEquipMontage(FName SectionName);
	bool CanDisarm();
	bool CanArm();
	void Disarm();
	void Enarm();
	virtual void Die_Implementation() override;

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

	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }

private:
	void SetHUDHealth();
	void InitializeSoulslikeOverlay();
	bool IsUnoccupied();
	bool HasEnoughStamina();

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	// Character Components

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY()
	USoulslikeOverlay* SoulslikeOverlay;

};
