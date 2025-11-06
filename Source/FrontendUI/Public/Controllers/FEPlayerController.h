// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FEPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FRONTENDUI_API AFEPlayerController : public APlayerController
{
	GENERATED_BODY()

	//~ Begin APlayerController Interface
	virtual void OnPossess(APawn* InPawn) override;
	//~ End APlayerController Interface
};
