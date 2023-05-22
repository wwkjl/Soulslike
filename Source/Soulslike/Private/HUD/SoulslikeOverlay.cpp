// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SoulslikeOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Enemy/Boss.h"

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

void USoulslikeOverlay::SetBossEngage(ABoss* Boss)
{
	if (BossProgressBar && BossName)
	{
		BossProgressBar->SetVisibility(ESlateVisibility::Visible);
		BossName->SetVisibility(ESlateVisibility::Visible);

		BossName->SetText(FText::FromName(Boss->GetBossName()));
	}
}

void USoulslikeOverlay::SetBossBarPercent(float Percent)
{
	if (BossProgressBar)
	{
		BossProgressBar->SetPercent(Percent);
	}
}

void USoulslikeOverlay::HideBossUI()
{
	if (BossProgressBar && BossName)
	{
		BossProgressBar->SetVisibility(ESlateVisibility::Hidden);
		BossName->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USoulslikeOverlay::SetGameResultText(bool bWon)
{
	if (GameResultText)
	{
		FString Result = bWon ? FString("Game Clear!") : FString("Game Over...");
		GameResultText->SetText(FText::FromString(Result));
	}
}
