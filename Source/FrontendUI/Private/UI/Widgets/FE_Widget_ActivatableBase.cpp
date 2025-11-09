// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/FE_Widget_ActivatableBase.h"
#include "Controllers/FEPlayerController.h"

AFEPlayerController* UFE_Widget_ActivatableBase::GetOwningFrontendController()
{
	if (!CachedOwningFrontendPC.IsValid())
	{
		CachedOwningFrontendPC = GetOwningPlayer<AFEPlayerController>();
	}

	return CachedOwningFrontendPC.IsValid()? CachedOwningFrontendPC.Get() : nullptr;
}
