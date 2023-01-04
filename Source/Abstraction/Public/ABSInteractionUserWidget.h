// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSWorldUserWidget.h"
#include "ABSInteractionUserWidget.generated.h"

class FText;

UCLASS()
class ABSTRACTION_API UABSInteractionUserWidget : public UABSWorldUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	FText InteractMessage;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
