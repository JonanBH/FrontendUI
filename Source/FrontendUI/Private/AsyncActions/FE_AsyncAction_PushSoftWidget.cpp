// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/FE_AsyncAction_PushSoftWidget.h"
#include "UI/Widgets/FE_Widget_ActivatableBase.h"
#include "Subsystems/FE_UISubsystem.h"

UFE_AsyncAction_PushSoftWidget* UFE_AsyncAction_PushSoftWidget::PushSoftWidget(const UObject* WorldContextObject,
	APlayerController* OwningPlayerController, TSoftClassPtr<UFE_Widget_ActivatableBase> InSoftWidgetClass,
	FGameplayTag InWidgetStackTag, bool bFocusOnNewlyPushedWidget)
{
	checkf(!InSoftWidgetClass.IsNull(), TEXT("PushSoftWidgetToStack was passed with a null soft widget class"))
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UFE_AsyncAction_PushSoftWidget* Node = NewObject<UFE_AsyncAction_PushSoftWidget>();

			Node->CachedOwningWorld = World;
			Node->CachedOwningPC = OwningPlayerController;
			Node->CachedSoftWidgetClass = InSoftWidgetClass;
			Node->CachedWidgetStackTag = InWidgetStackTag;
			Node->bCachedFocusOnNewlyPushedWidget = bFocusOnNewlyPushedWidget;

			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}

void UFE_AsyncAction_PushSoftWidget::Activate()
{
	Super::Activate();

	UFE_UISubsystem* FEUISubsystem = UFE_UISubsystem::GetInstance(CachedOwningWorld.Get());

	FEUISubsystem->PushSoftWidgetToStackAsync(CachedWidgetStackTag, CachedSoftWidgetClass,
		[this](EAsyncPushWidgetState InPushState, UFE_Widget_ActivatableBase* PushedWidget)
		{
			switch (InPushState)
			{
			case EAsyncPushWidgetState::OnCreatedBeforePush:
				PushedWidget->SetOwningPlayer(CachedOwningPC.Get());

				OnWidgetCreatedBeforePush.Broadcast(PushedWidget);
				break;
				
			case EAsyncPushWidgetState::AfterPush:
				OnWidgetCreatedAfterPush.Broadcast(PushedWidget);

				if (bCachedFocusOnNewlyPushedWidget)
				{
					if (UWidget* WidgetToFocus = PushedWidget->GetDesiredFocusTarget())
					{
						WidgetToFocus->SetFocus();
					}
				}

				SetReadyToDestroy();
				break;
				
			default:
					break;
			}
		});
}
