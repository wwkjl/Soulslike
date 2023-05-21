// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SoulslikeHUD.generated.h"


class USoulslikeOverlay;
class ABoss;
class ASoulslikeGameMode;


UCLASS()
class SOULSLIKE_API ASoulslikeHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBossEngage(ABoss* EngagedBoss);

	UFUNCTION()
	void OnBossDefeat(ABoss* DefeatedBoss);

	UFUNCTION()
	void OnBossGetHit(float BossHealthPercent);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Soulslike")
	TSubclassOf<USoulslikeOverlay> SoulslikeOverlayClass;

	USoulslikeOverlay* SoulslikeOverlay;
	ABoss* StageBoss;
	ASoulslikeGameMode* SoulslikeGameMode;

public:
	FORCEINLINE USoulslikeOverlay* GetSoulslikeOverlay() const { return SoulslikeOverlay; }
};
