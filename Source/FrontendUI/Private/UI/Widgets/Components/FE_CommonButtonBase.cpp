// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Components/FE_CommonButtonBase.h"
#include "Subsystems//FE_UISubsystem.h"
#include "CommonTextBlock.h"

void UFE_CommonButtonBase::SetButtonText(FText InText)
{
	if (!CommonTextBlock_ButtonText) return;
	if (InText.IsEmpty()) return;

	CommonTextBlock_ButtonText->SetText(bUseUppercaseButtonText ?InText.ToUpper() : InText);
}

void UFE_CommonButtonBase::NativePreConstruct()
{
	Super::NativePreConstruct();

	SetButtonText(ButtonDisplayText);
}

void UFE_CommonButtonBase::NativeOnCurrentTextStyleChanged()
{
	Super::NativeOnCurrentTextStyleChanged();

	TSubclassOf<UCommonTextStyle> TextStyle = GetCurrentTextStyleClass();
	if (CommonTextBlock_ButtonText && IsValid(TextStyle))
	{
		CommonTextBlock_ButtonText->SetStyle(GetCurrentTextStyleClass());
	}
}

void UFE_CommonButtonBase::NativeOnHovered()
{
	Super::NativeOnHovered();

	if (ButtonDescriptionText.IsEmpty()) return;

	UFE_UISubsystem::GetInstance(this)->OnButtonDescriptionTextUpdated.Broadcast(this,
		ButtonDescriptionText);
}

void UFE_CommonButtonBase::NativeOnUnhovered()
{
	Super::NativeOnUnhovered();

	UFE_UISubsystem::GetInstance(this)->OnButtonDescriptionTextUpdated.Broadcast(this,
		FText::GetEmpty());
}
