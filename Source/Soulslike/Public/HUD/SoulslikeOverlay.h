// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoulslikeOverlay.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;


UCLASS()
class SOULSLIKE_API USoulslikeOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetHealthBarPercent(float Percent);
	void SetStaminaBarPercent(float Percent);
	void SetGold(int32 Gold);
	void SetSoul(int32 Soul);
	void SetPotion(int32 Potion);

private:
	UPROPERTY(meta = (BindWIdget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWIdget))
	UProgressBar* StaminaProgressBar;

	UPROPERTY(meta = (BindWIdget))
	UTextBlock* GoldCountText;

	UPROPERTY(meta = (BindWIdget))
	UTextBlock* SoulCountText;

	UPROPERTY(meta = (BindWIdget))
	UTextBlock* PotionCountText;
};
