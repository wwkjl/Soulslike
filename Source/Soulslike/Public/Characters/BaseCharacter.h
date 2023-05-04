// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterType.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;


UCLASS()
class SOULSLIKE_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

protected:
	virtual void BeginPlay() override;

	// Combat

	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual void Attack1();

	UFUNCTION(BlueprintNativeEvent)
	void Die();

	void DirectionalHitReact(const FVector& ImpactPoint);
	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	virtual void HandleDamage(float DamageAmount);
	void DisableCapsue();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Combat")
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double WarpTargetDistance = 75.f;

	// Montage

	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);
	virtual int32 PlayAttack1Montage();
	virtual int32 PlayDeathMontage();
	virtual void PlayDodgeMontage();
	void StopAttack1Montage();

	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();

	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UFUNCTION(BlueprintCallable)
	virtual void DodgeEnd();

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	AWeapon* EquippedWeapon;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UAttributeComponent* Attributes;

	virtual bool CanAttack();
	bool IsAlive();

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;


public:	
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return DeathPose; }

private:
	void PlayHitReactMontage(const FName& SectionName);
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* HitParticles;

	// Animation Montages

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* Attack1Montage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, Category = "Montages")
	TArray<FName> Attack1MontageSections;

	UPROPERTY(EditAnywhere, Category = "Montages")
	TArray<FName> DeathMontageSections;
};
