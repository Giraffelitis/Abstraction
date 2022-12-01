// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ABSInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractedWith, class AActor*, InstigatingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionSuccess, class AActor*, FocusedActor);

class UABSWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UABSInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnInteractedWith OnInteractedWith;

	UPROPERTY(BlueprintAssignable)
	FOnInteractedWith OnInteractionSuccess;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer SecurityTags;

	// Creates In Editor option to select proper Widget
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UABSWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UABSWorldUserWidget* DefaultWidgetInstance;

	void InteractedWith(AActor* InstigatingActor) const;

	void InteractionSuccessful(AActor* InstigatingActor) const;
	
};
