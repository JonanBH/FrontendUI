// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/FE_UISubsystem.h"
#include "Engine/AssetManager.h"
#include "UI/Widgets/FE_Widget_ActivatableBase.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
#include "FrontEndDebugHelper.h"
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
	check(InSoftWidgetClass.IsNull());

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
