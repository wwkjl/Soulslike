// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SoulslikeHUD.h"
#include "HUD/SoulslikeOverlay.h"

void ASoulslikeHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if (Controller && SoulslikeOverlayClass)
		{
			SoulslikeOverlay = CreateWidget<USoulslikeOverlay>(Controller, SoulslikeOverlayClass);
			SoulslikeOverlay->AddToViewport();
		}
	}
}
