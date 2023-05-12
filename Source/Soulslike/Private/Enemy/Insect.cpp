// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Insect.h"
#include "Projectile/Projectile.h"
#include "Kismet/KismetMathLibrary.h"

AInsect::AInsect()
{
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(GetMesh());
}

void AInsect::ChooseAttack()
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

void AInsect::Attack2()
{
	Super::Attack2();

	if (ProjectileClass && CombatTarget)
	{
		FVector Location = ProjectileSpawnPoint->GetComponentLocation();
		FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CombatTarget->GetActorLocation());

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
		Projectile->SetOwner(this);
	}
}

bool AInsect::IsOutsideMeleeRange()
{
	return !InTargetRange(CombatTarget, MeleeRadius);
}
