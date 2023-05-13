// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss.h"
#include "GameFramework/CharacterMovementComponent.h"


ABoss::ABoss()
{
}

void ABoss::ChooseAttack()
{
	if (BossPhase == EBossPhase::EBP_Phase1)	// Health more than 50, Phase 1
	{
		if (IsOutsideMeleeRange())
		{
			Attack2();
		}
		else
		{
			Attack1();
		}
	}
	else
	{
		if (IsOutsideMeleeRange())
		{
			AttackJump();
		}
		else
		{
			AttackRush();
		}
	}
}

void ABoss::Transform()
{
	PlayMontageName(TransformMontage);
	BossPhase = EBossPhase::EBP_Phase2;
}

void ABoss::AttackRush()
{
	if (CombatTarget == nullptr) return;

	EnemyState = EEnemyState::EES_Engaged;

	AttackTargetLocation = CombatTarget->GetActorLocation();
	GetCharacterMovement()->MaxWalkSpeed = RushSpeed;
	PlayMontageName(AttackRushMontage);
}

void ABoss::AttackJump()
{
	if (CombatTarget == nullptr) return;

	EnemyState = EEnemyState::EES_Engaged;

	AttackTargetLocation = CombatTarget->GetActorLocation();
	// Damage Up
	PlayMontageName(AttackJumpMontage);
}

void ABoss::PlayMontageName(UAnimMontage* Montage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && Montage)
	{
		AnimInstance->Montage_Play(Montage, 1.f);
	}
}

void ABoss::TransformEnd()
{
	EnemyState = EEnemyState::EES_NoState;
	CheckCombatTarget();
}

void ABoss::AttackRushEnd()
{
	GetCharacterMovement()->MaxWalkSpeed = ChasingSpeed;

	EnemyState = EEnemyState::EES_NoState;
	CheckCombatTarget();
}

void ABoss::AttackJumpEnd()
{
	// Damage Down

	EnemyState = EEnemyState::EES_NoState;
	CheckCombatTarget();
}
