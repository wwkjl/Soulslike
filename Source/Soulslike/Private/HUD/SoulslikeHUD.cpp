// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SoulslikeHUD.h"
#include "HUD/SoulslikeOverlay.h"
#include "GameMode/SoulslikeGameMode.h"
#include "Kismet/Gameplaystatics.h"
#include "Enemy/Boss.h"

void ASoulslikeHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		StageBoss = Cast<ABoss>(UGameplayStatics::GetActorOfClass(World, ABoss::StaticClass()));
		SoulslikeGameMode = Cast<ASoulslikeGameMode>(UGameplayStatics::GetGameMode(this));

		if (Controller && SoulslikeOverlayClass)
		{
			SoulslikeOverlay = CreateWidget<USoulslikeOverlay>(Controller, SoulslikeOverlayClass);
			SoulslikeOverlay->AddToViewport();

			if (StageBoss)
			{
				StageBoss->OnBossEngage.AddDynamic(this, &ASoulslikeHUD::OnBossEngage);
				StageBoss->OnBossDefeat.AddDynamic(this, &ASoulslikeHUD::OnBossDefeat);
				StageBoss->OnBossGetHit.AddDynamic(this, &ASoulslikeHUD::OnBossGetHit);
			}
		}
	}
}

void ASoulslikeHUD::OnBossEngage(ABoss* EngagedBoss)
{
	if (SoulslikeOverlay)
	{
		SoulslikeOverlay->SetBossEngage(EngagedBoss);
	}
}

void ASoulslikeHUD::OnBossDefeat(ABoss* DefeatedBoss)
{
	if (SoulslikeOverlay)
	{
		SoulslikeOverlay->HideBossUI();
	}

	if (SoulslikeGameMode)
	{
		SoulslikeGameMode->WonGame();
	}
}

void ASoulslikeHUD::OnBossGetHit(float BossHealthPercent)
{
	if (SoulslikeOverlay)
	{
		SoulslikeOverlay->SetBossBarPercent(BossHealthPercent);
	}
}
