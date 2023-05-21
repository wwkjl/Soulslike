// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SoulslikeGameMode.h"

void ASoulslikeGameMode::WonGame()
{
	UE_LOG(LogTemp, Warning, TEXT("WIN"));
}

void ASoulslikeGameMode::LoseGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Lose"));
}

void ASoulslikeGameMode::BeginPlay()
{
	Super::BeginPlay();
}
