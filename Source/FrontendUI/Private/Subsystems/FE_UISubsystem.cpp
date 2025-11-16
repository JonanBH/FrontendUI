// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FE_UISubsystem.h"

#include "FE_FunctionLibrary.h"
#include "Engine/AssetManager.h"
#include "UI/Widgets/FE_Widget_ActivatableBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "FrontEndDebugHelper.h"
#include "AbilitySystem/FETags.h"
#include "UI/Widgets/FE_Widget_ConfirmScreen.h"
#include "UI/Widgets/FE_Widget_PrimaryLayout.h"


UFE_UISubsystem* UFE_UISubsystem::GetInstance(const UObject* WorldContextObject)
{
	if (!GEngine) return nullptr;

	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::Assert);

	if (!World) return nullptr;

	UGameInstance* GameInstance = World->GetGameInstance();

	if (!GameInstance) return nullptr;
		
	return UGameInstance::GetSubsystem<UFE_UISubsystem>(World->GetGameInstance());
}

bool UFE_UISubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	if (!CastChecked<UGameInstance>(Outer)->IsDedicatedServerInstance())
	{
		TArray<UClass*> FoundClasses;
		GetDerivedClasses(GetClass(), FoundClasses);

		return FoundClasses.IsEmpty();
	}

	return false;
}

void UFE_UISubsystem::RegisterCreatedPrimaryLayoutWidget(UFE_Widget_PrimaryLayout* InCreatedWidget)
{
	check(InCreatedWidget);
	CreatedPrimaryLayout = InCreatedWidget;

	Debug::Print("Primary layout widget stored");
}

void UFE_UISubsystem::PushSoftWidgetToStackAsync(const FGameplayTag& InWidgetStackTag,
	TSoftClassPtr<UFE_Widget_ActivatableBase> InSoftWidgetClass,
	TFunction<void(EAsyncPushWidgetState, UFE_Widget_ActivatableBase*)> AsyncPushStateCallback)
{
	check(!InSoftWidgetClass.IsNull());

	UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		InSoftWidgetClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[InSoftWidgetClass, InWidgetStackTag, this, AsyncPushStateCallback]()
			{
				UClass* LoadedWidgetClass = InSoftWidgetClass.Get();
				check(LoadedWidgetClass && CreatedPrimaryLayout);

				UCommonActivatableWidgetContainerBase* FoundWidgetContainer = CreatedPrimaryLayout->FindWidgetStackByTag(InWidgetStackTag);
				UFE_Widget_ActivatableBase* CreatedWidget = FoundWidgetContainer->AddWidget<UFE_Widget_ActivatableBase>(LoadedWidgetClass,
					[AsyncPushStateCallback](UFE_Widget_ActivatableBase& CreatedWidgetInstance)
					{
						AsyncPushStateCallback(EAsyncPushWidgetState::OnCreatedBeforePush, &CreatedWidgetInstance);
					});

				AsyncPushStateCallback(EAsyncPushWidgetState::AfterPush, CreatedWidget);
			})
			);
}

void UFE_UISubsystem::PushConfirmScreenToModalStackAsync(EConfirmScreenType InScreenType, const FText& InScreenTitle,
	const FText& InScreenMsg, TFunction<void(EConfirmScreenButtonType)> ButtonClickedCallback)
{
	UConfirmScreenInfoObject* CreatedInfoObject = nullptr;
	switch (InScreenType)
	{
	case EConfirmScreenType::Ok:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOKScreen(InScreenTitle, InScreenMsg);
		break;
	case EConfirmScreenType::YesNo:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateYesNoScreen(InScreenTitle, InScreenMsg);
		break;
	case EConfirmScreenType::OkCancel:
		CreatedInfoObject = UConfirmScreenInfoObject::CreateOkCancelScreen(InScreenTitle, InScreenMsg);
		break;
	case EConfirmScreenType::Unknown:
		break;
	default:
		break;
	}

	check(CreatedInfoObject);

	PushSoftWidgetToStackAsync(
		FETags::UI::Frontend_WidgetStack_Modal,
		UFE_FunctionLibrary::GetFrontendSoftWidgetClassByTag(FETags::Widgets::Frontend_Widget_ConfirmScreen),
		[CreatedInfoObject, ButtonClickedCallback](EAsyncPushWidgetState InPushState, UFE_Widget_ActivatableBase* PushedWidget)
		{
			if (InPushState == EAsyncPushWidgetState::OnCreatedBeforePush)
			{
				UFE_Widget_ConfirmScreen* CreatedConfirmScreen = CastChecked<UFE_Widget_ConfirmScreen>(PushedWidget);
				CreatedConfirmScreen->InitConfirmScreen(CreatedInfoObject, ButtonClickedCallback);
			}
		}
		);
}
