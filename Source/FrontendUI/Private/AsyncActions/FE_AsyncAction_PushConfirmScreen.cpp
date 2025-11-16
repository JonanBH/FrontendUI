// Fill out your copyright notice in the Description page of Project Settings.


#include "AsyncActions/FE_AsyncAction_PushConfirmScreen.h"

#include "Subsystems/FE_UISubsystem.h"

void UFE_AsyncAction_PushConfirmScreen::Activate()
{
	Super::Activate();
	UFE_UISubsystem::GetInstance(CachedOwningWorld.Get())->PushConfirmScreenToModalStackAsync(
		CachedScreenType,
		CachedScreenTitle,
		CachedScreenMessage,
		[this](EConfirmScreenButtonType ClickedButtonType)
		{
			OnButtonClicked.Broadcast(ClickedButtonType);

			SetReadyToDestroy();
		});
}

UFE_AsyncAction_PushConfirmScreen* UFE_AsyncAction_PushConfirmScreen::PushConfirmScreen(
	const UObject* WorldContextObject, EConfirmScreenType ScreenType, FText InScreenTitle, FText InScreenMessage)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			UFE_AsyncAction_PushConfirmScreen* Node= NewObject<UFE_AsyncAction_PushConfirmScreen>();
			
			Node->CachedOwningWorld = World;
			Node->CachedScreenType = ScreenType;
			Node->CachedScreenTitle = InScreenTitle;
			Node->CachedScreenMessage = InScreenMessage;

			Node->RegisterWithGameInstance(World);

			return Node;
		}
	}

	return nullptr;
}
