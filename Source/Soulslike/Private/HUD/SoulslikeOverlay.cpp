// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SoulslikeOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USoulslikeOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void USoulslikeOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void USoulslikeOverlay::SetGold(int32 Gold)
{
	if (GoldCountText)
	{
		GoldCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Gold)));
	}
}

void USoulslikeOverlay::SetSoul(int32 Soul)
{
	if (SoulCountText)
	{
		SoulCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Soul)));
	}
}

void USoulslikeOverlay::SetPotion(int32 Potion)
{
	if (PotionCountText)
	{
		PotionCountText->SetText(FText::FromString(FString::Printf(TEXT("%d"), Potion)));
	}
}
