// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Interfaces/HitInterface.h"
#include "Camera/CameraShakeBase.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	SetRootComponent(ProjectileMesh);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Sphere"));
	CollisionSphere->SetupAttachment(GetRootComponent());
	CollisionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = ProjectileMaxSpeed;
	ProjectileMovementComponent->InitialSpeed = ProjectileSpeed;

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	TrailParticles->SetupAttachment(GetRootComponent());
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(1.f);

	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnSphereOverlap);
	if (LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	if (OtherActor && OtherActor != this && !ActorIsSameType(OtherActor))
	{
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			MyOwnerInstigator,
			this,
			UDamageType::StaticClass()
		);

		ExecuteGetHit(OtherActor);

		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
	}

	Destroy();
}

bool AProjectile::ActorIsSameType(AActor* OtherActor)
{
	return GetOwner()->ActorHasTag(TEXT("Enemy")) && OtherActor->ActorHasTag(TEXT("Enemy"));
}

void AProjectile::ExecuteGetHit(AActor* OtherActor)
{
	IHitInterface* HitInterface = Cast<IHitInterface>(OtherActor);
	if (HitInterface)
	{
		HitInterface->Execute_GetHit(OtherActor, GetActorLocation(), GetOwner());
	}
}
