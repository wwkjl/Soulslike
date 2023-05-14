// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Boss.h"
#include "Items/Weapon/Weapon.h"
#include "Components/BoxComponent.h"
#include "Projectile/Projectile.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


ABoss::ABoss()
{
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();

	SpawnDefaultBossWeapon();
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

void ABoss::Attack2()
{
	if (CombatTarget == nullptr) return;

	EnemyState = EEnemyState::EES_Engaged;
	PlayAttack2Montage();
}

void ABoss::SetWeapon2CollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon2 && EquippedWeapon2->GetWeaponBox())
	{
		EquippedWeapon2->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		EquippedWeapon2->IgnoreActors.Empty();
	}
}

void ABoss::SetWeapon3CollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon3 && EquippedWeapon3->GetWeaponBox())
	{
		EquippedWeapon3->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		EquippedWeapon3->IgnoreActors.Empty();
	}
}

void ABoss::Transform()
{
	PlayMontageName(TransformMontage);
	BossPhase = EBossPhase::EBP_Phase2;
}

void ABoss::Engage()
{
	if (CombatTarget == nullptr) return;

	EnemyState = EEnemyState::EES_Engaged;
	PlayMontageName(EngageMontage);
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

void ABoss::SpawnDefaultBossWeapon()
{
	UWorld* World = GetWorld();
	if (World && WeaponClass2 && WeaponClass3)
	{
		AWeapon* DefaultWeapon2 = World->SpawnActor<AWeapon>(WeaponClass2);
		DefaultWeapon2->Equip(GetMesh(), FName("Weapon2Socket"), this, this, false);
		EquippedWeapon2 = DefaultWeapon2;

		AWeapon* DefaultWeapon3 = World->SpawnActor<AWeapon>(WeaponClass3);
		DefaultWeapon3->Equip(GetMesh(), FName("Weapon3Socket"), this, this, false);
		EquippedWeapon3 = DefaultWeapon3;
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
	EnemyState = EEnemyState::EES_NoState;
	CheckCombatTarget();
}
