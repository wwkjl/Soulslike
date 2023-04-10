// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include "DrawDebugHelpers.h"
#include "Soulslike/DebugMacros.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogTemp, Warning, TEXT("Hello World!"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 60.f, FColor::Cyan, FString("Item OnScreen Message"));
	}

	UWorld* World = GetWorld();

	if (World)
	{
		FVector Location = GetActorLocation();
		FVector Forward = GetActorForwardVector();
		DRAW_DEBUG_SPHERE(Location);
		DRAW_DEBUG_VECTOR(Location, Location + Forward * 100.f);
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

