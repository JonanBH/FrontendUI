// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"
#include "FE_AsyncAction_PushSoftWidget.generated.h"

class UFE_Widget_ActivatableBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPushSoftWidgetDelegate, UFE_Widget_ActivatableBase*, PushedWidget);

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFE_AsyncAction_PushSoftWidget : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject", HidePin = "WorldContextObject", BlueprintInternalUseOnly = true, DisplayName = "Push Soft Widget To Widget Stack"))
	static UFE_AsyncAction_PushSoftWidget* PushSoftWidget(const UObject* WorldContextObject,
		APlayerController* OwningPlayerController, TSoftClassPtr<UFE_Widget_ActivatableBase> InSoftWidgetClass,
		UPARAM(meta=(Categories = "FETags.UI")) FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget = true);

	//~ Begin UBlueprintAsyncActionBase interface
	virtual void Activate() override;
	//~ End UBlueprintAsyncActionBase interface
	
	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedBeforePush;

	UPROPERTY(BlueprintAssignable)
	FOnPushSoftWidgetDelegate OnWidgetCreatedAfterPush;

private:
	TWeakObjectPtr<UWorld> CachedOwningWorld;
	TWeakObjectPtr<APlayerController> CachedOwningPC;
	TSoftClassPtr<UFE_Widget_ActivatableBase> CachedSoftWidgetClass;
	FGameplayTag CachedWidgetStackTag;
	bool bCachedFocusOnNewlyPushedWidget = false;
	
};
