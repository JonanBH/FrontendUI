// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/FE_Widget_PrimaryLayout.h"

#include "FrontEndDebugHelper.h"

UCommonActivatableWidgetContainerBase* UFE_Widget_PrimaryLayout::FindWidgetStackByTag(const FGameplayTag& Tag) const
{
	checkf(RegisteredWidgetStackMap.Contains(Tag), TEXT("Can not find the widget stack by the tag %s"), *Tag.ToString());

	return RegisteredWidgetStackMap.FindRef(Tag);
}

void UFE_Widget_PrimaryLayout::RegisterWidgetStack(UPARAM(meta = (Categories = "FETags.UI"))FGameplayTag InStackTag,
	UCommonActivatableWidgetContainerBase* InStack)
{
	if (IsDesignTime()) return;

	if (RegisteredWidgetStackMap.Contains(InStackTag)) return;
	
	RegisteredWidgetStackMap.Add(InStackTag, InStack);

}
