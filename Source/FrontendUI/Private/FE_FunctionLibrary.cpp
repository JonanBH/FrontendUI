// Fill out your copyright notice in the Description page of Project Settings.


#include "FE_FunctionLibrary.h"
#include "FrontendSettings/FE_DeveloperSettings.h"

TSoftClassPtr<UFE_Widget_ActivatableBase> UFE_FunctionLibrary::GetFrontendSoftWidgetClassByTag(FGameplayTag InTag)
{
	const UFE_DeveloperSettings* FEDeveloperSettings = GetDefault<UFE_DeveloperSettings>();
	checkf(FEDeveloperSettings->FrontendWidgetMap.Contains(InTag),
		TEXT("Could not find the corresponding widget under the tag %s"), *InTag.ToString());

	return FEDeveloperSettings->FrontendWidgetMap.FindRef(InTag);
}
