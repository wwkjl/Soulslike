// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/SoulslikeGameMode.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

ASoulslikeGameMode::ASoulslikeGameMode()
{
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->bAutoActivate = false;
}

void ASoulslikeGameMode::WonGame()
{
	UE_LOG(LogTemp, Warning, TEXT("WIN"));
}

void ASoulslikeGameMode::LoseGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Lose"));
}

void ASoulslikeGameMode::BossEngage()
{
	PlayMusic(BossMusicCue);
}

void ASoulslikeGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayMusic(MainMusicCue);
}

void ASoulslikeGameMode::PlayMusic(USoundCue* Music)
{
	if (AudioComponent && Music)
	{
		AudioComponent->Stop();
		AudioComponent->SetSound(Music);
		AudioComponent->Play();
	}
}
