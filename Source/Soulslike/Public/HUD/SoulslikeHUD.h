// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SoulslikeHUD.generated.h"


class USoulslikeOverlay;


UCLASS()
class SOULSLIKE_API ASoulslikeHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Soulslike")
	TSubclassOf<USoulslikeOverlay> SoulslikeOverlayClass;

	USoulslikeOverlay* SoulslikeOverlay;

public:
	FORCEINLINE USoulslikeOverlay* GetSoulslikeOverlay() const { return SoulslikeOverlay; }
};
