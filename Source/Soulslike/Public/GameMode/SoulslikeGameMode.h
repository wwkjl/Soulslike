// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SoulslikeGameMode.generated.h"

/**
 * 
 */

class UAudioComponent;
class USoundCue;


UCLASS()
class SOULSLIKE_API ASoulslikeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ASoulslikeGameMode();

	UFUNCTION()
	void WonGame();

	UFUNCTION()
	void LoseGame();

	UFUNCTION()
	void BossEngage();

protected:
	virtual void BeginPlay() override;

private:
	void PlayMusic(USoundCue* Music);

	UPROPERTY(EditAnywhere, Category = "Audio")
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* MainMusicCue;

	UPROPERTY(EditAnywhere, Category = "Audio")
	USoundCue* BossMusicCue;
};
