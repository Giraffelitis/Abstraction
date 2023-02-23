// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ABSGameplayInterface.h"
#include "ABSInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractedWith, class AActor*, InstigatingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionFailure, class AActor*, InstigatingActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionSuccess, class AActor*, InstigatingActor);

class UABSWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UABSInteractionComponent : public UActorComponent, public IABSGameplayInterface
{
	GENERATED_BODY()

public:
	
	UABSInteractionComponent();

	UPROPERTY(BlueprintAssignable)
	FOnInteractedWith OnInteractedWith;

	UPROPERTY(BlueprintAssignable)
	FOnInteractionFailure OnInteractionFailure;
	
	UPROPERTY(BlueprintAssignable)
	FOnInteractionSuccess OnInteractionSuccess;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer ActiveGameplayTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer RequiredSecurityTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer GrantedSecurityTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
	FText InteractFailMessage;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Message")
	FText InteractSuccessMessage;
	
	// Creates In Editor option to select proper Widget
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UABSWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UABSWorldUserWidget* DefaultWidgetInstance;
	
	bool InteractedWith(AActor* InstigatingActor);

	void CheckInteractionSuccess(AActor* InstigatingActor) const;

};

