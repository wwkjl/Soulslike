// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterType.h"
#include "Enemy.generated.h"

class UHealthBarComponent;
class UPawnSensingComponent;

UCLASS()
class SOULSLIKE_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;
	virtual void Die_Implementation() override;
	virtual void Attack1() override;
	virtual bool CanAttack() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void AttackEnd() override;
	bool IsTargetable_Implementation() const override;

	virtual void ChaseTarget();
	virtual void ChooseAttack();
	virtual void Attack2();
	int32 PlayAttack2Montage();
	void StopAttack2Montage();
	bool IsOutsideCombatRadius();
	bool IsOutsideAttackRadius();
	bool InTargetRange(AActor* Target, double Radius);

	UPROPERTY(EditAnywhere, Category = "Combat")
	float DeathLifeSpan = 8.f;

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void NoiseHeard(APawn* HeardActor, const FVector& Location, float Volume);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float PatrollingSpeed = 125.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double CombatRadius = 800.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double AttackRadius = 150.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	double AcceptanceRadius = 45.f;

public:	
	virtual void Tick(float DeltaTime) override;
	void CheckPatrolTarget();
	void CheckCombatTarget();
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

private:
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AWeapon> WeaponClass;

	// Navigation

	UPROPERTY()
	class AAIController* EnemyController;

	// Current Patrol Target
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 3.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	// AI Behaviour

	void InitializeEnemy();
	void HideHealthBar();
	void ShowHealthBar();
	void LoseInterest();
	void StartPatrolling();
	bool IsChasing();
	bool IsAttacking();
	bool IsDead();
	bool IsEngaged();
	bool ShouldChaseTarget(AActor* Target);
	void ClearPatrolTimer();
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();
	void SpawnDefaultWeapon();
	void SpawnSoul();

	// Combat
	
	void StartAttackTimer();
	void ClearAttackTimer();
	bool IsTargetable = true;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float Attack2Ratio = 0.3f;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class ASoul> SoulClass;

	// Animation Montages

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* Attack2Montage;

	UPROPERTY(EditAnywhere, Category = "Montages")
	TArray<FName> Attack2MontageSections;
};
