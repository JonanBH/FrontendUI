// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "FE_CommonButtonBase.generated.h"

class UCommonTextBlock;

/**
 * 
 */
UCLASS(Abstract, BlueprintType, meta = (DisableNativeTick))
class FRONTENDUI_API UFE_CommonButtonBase : public UCommonButtonBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetButtonText(FText InText);

	
private:
	//~ Begin UUserWidget Interface
	virtual void NativePreConstruct() override;
	//~ End UUSerWidget Interface

	//~Begin UCommonButtonBase Interface
	virtual void NativeOnCurrentTextStyleChanged() override;
	virtual void NativeOnHovered() override;
	virtual void NativeOnUnhovered() override;
	//~End UCommonButtonBase Interface
	
	//**** Bound Widgets ****//
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UCommonTextBlock> CommonTextBlock_ButtonText;
	//**** Bound Widgets ****//

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontdnd Button", meta = (AllowPrivateAccess = true))
	FText ButtonDisplayText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontdnd Button", meta = (AllowPrivateAccess = true))
	bool bUseUppercaseButtonText = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Frontdnd Button", meta = (AllowPrivateAccess = true))
	FText ButtonDescriptionText;

};
