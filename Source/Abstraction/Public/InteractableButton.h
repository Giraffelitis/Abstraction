// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "InteractableButton.generated.h"

class ATriggerBox;
class IConsoleVariable;

UENUM()
enum class EButtonState
{
	BS_In = 0	UMETA(DisplayName = "In"),
	BS_Out = 1	UMETA(DisplayName = "Out")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABSTRACTION_API UInteractableButton : public UInteractionComponent
{
	GENERATED_BODY()
	
public:
	UInteractableButton();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	static void OnDebugToggled(IConsoleVariable* Var);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//binded to interaction input from player
	void InteractionStart() override;

	//request to open the door
	UFUNCTION(BlueprintCallable)
	void ButtonPressed();

	//called internally when door has finished opening
	void OnButtonPressed();

	//request to close the door
	UFUNCTION(BlueprintCallable)
	void ButtonReleased();

	//called internally when door has finished Closing
	void OnButtonReleased();

	UFUNCTION(BlueprintCallable)
	bool IsPressed() { return ButtonState == EButtonState::BS_In; }

	UFUNCTION(BlueprintCallable)
	bool IsNotPressed() { return ButtonState == EButtonState::BS_Out; }

	UPROPERTY(EditAnywhere)
	float TimeToRelease = 1.0f;

	float CurrentPressedTime = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerBox* TriggerBox;

	UPROPERTY(BlueprintReadOnly)
	EButtonState ButtonState;
};
