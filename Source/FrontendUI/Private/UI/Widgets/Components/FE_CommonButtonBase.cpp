// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/Components/FE_CommonButtonBase.h"
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
