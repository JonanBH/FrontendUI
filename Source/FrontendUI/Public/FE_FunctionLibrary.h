// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"
#include "FE_FunctionLibrary.generated.h"

class UFE_AsyncAction_PushSoftWidget;
/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFE_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Frontend Function Library")
	static TSoftClassPtr<UFE_Widget_ActivatableBase> GetFrontendSoftWidgetClassByTag(UPARAM(meta = (Categories = "FETags.Widgets"))FGameplayTag InTag);
};
