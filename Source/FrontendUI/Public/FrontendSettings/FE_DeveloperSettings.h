// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GameplayTagContainer.h"
#include "FE_DeveloperSettings.generated.h"

class UFE_Widget_ActivatableBase;
/**
 * 
 */
UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Frontend UI Settings"))
class FRONTENDUI_API UFE_DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "Widget Reference", meta = (ForceInlineRow, Categories = "FETags.Widgets"))
	TMap<FGameplayTag, TSoftClassPtr<UFE_Widget_ActivatableBase>> FrontendWidgetMap;
};
