// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ABSInteractionComponent.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "ABSInteractAction.generated.h"

class UABSInteraction;
class UABSInteractionComponent;
class UABSWorldUserWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABSTRACTION_API UABSInteractAction : public UActorComponent
{
	GENERATED_BODY()

public:
	UABSInteractAction();

	void Initialize(UABSInteractionComponent* NewActionComp);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void PrimaryInteract();
	
protected:

	void Interact(AActor* InFocus);
	
	void FindBestInteractable();

	virtual void BeginPlay() override;

	/* Call this Object to add action functionality to actors and other objects */
	UPROPERTY()
	UABSInteractionComponent* InteractionComp;
	
	UPROPERTY()
	AActor* FocusedActor;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceDistance;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float TraceRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UABSWorldUserWidget> DefaultWidgetClass;

	UPROPERTY()
	UABSWorldUserWidget* DefaultWidgetInstance;

	/* Tag Container used to get the parent component the actions are attached to */
    UFUNCTION(BlueprintCallable, Category = "Action")
    UABSInteractionComponent* GetOwningComponent() const;
    
    /* Tag Container used to add Tags to owning actor when activated, and to remove when action stops */
    UPROPERTY(EditDefaultsOnly, Category = "Tags")
    FGameplayTagContainer GrantsTags;

};
