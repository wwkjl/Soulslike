// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SoulslikeGameMode.generated.h"

/**
 * 
 */



UCLASS()
class SOULSLIKE_API ASoulslikeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void WonGame();

	UFUNCTION()
	void LoseGame();

protected:
	virtual void BeginPlay() override;
};
