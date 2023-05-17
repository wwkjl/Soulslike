// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/Enemy.h"
#include "Insect.generated.h"

/**
 * 
 */
UCLASS()
class SOULSLIKE_API AInsect : public AEnemy
{
	GENERATED_BODY()
	
public:
	AInsect();

protected:
	void ChooseAttack() override;
	void Attack2() override;
	bool IsOutsideMeleeRange();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void ThrowProjectile();

	UPROPERTY(EditAnywhere, Category = "Combat")
	double MeleeRadius = 150.f;
};
