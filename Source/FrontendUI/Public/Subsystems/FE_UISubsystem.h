// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UI/Widgets/FE_Widget_ActivatableBase.h"
#include "FE_UISubsystem.generated.h"

class UFE_CommonButtonBase;
class UFE_Widget_ActivatableBase;
class UFE_Widget_PrimaryLayout;
struct FGameplayTag;

enum class EAsyncPushWidgetState : uint8
{
	OnCreatedBeforePush,
	AfterPush,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnButtonDescriptionTextUpdatedDelegate, UFE_CommonButtonBase*,
	BroadcastingButton, FText, DescriptionText);

/**
 * 
 */
UCLASS()
class FRONTENDUI_API UFE_UISubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()


public:
	static UFE_UISubsystem* GetInstance(const UObject* WorldContextObject);

	//~Begin USubsystem Interface
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;
	//~End USubsystem Interface

	UFUNCTION(BlueprintCallable)
	void RegisterCreatedPrimaryLayoutWidget(UFE_Widget_PrimaryLayout* InCreatedWidget);

	void PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
		TSoftClassPtr<UFE_Widget_ActivatableBase> InSoftWidgetClass,
		TFunction<void(EAsyncPushWidgetState, UFE_Widget_ActivatableBase*)> AsyncPushStateCallback);

	UPROPERTY(BlueprintAssignable)
	FOnButtonDescriptionTextUpdatedDelegate OnButtonDescriptionTextUpdated;
	
private:
	UPROPERTY(Transient)
	TObjectPtr<UFE_Widget_PrimaryLayout> CreatedPrimaryLayout;
};
