// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.h"
#include "ButtonInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;
class UAudioComponent;
class UTextRenderComponent;

UENUM()
enum class EButtonState
{
	BS_In = 0	UMETA(DisplayName = "In"),
	BS_Out = 1	UMETA(DisplayName = "Out")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABSTRACTION_API UButtonInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UButtonInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//request to press the button
	UFUNCTION(BlueprintCallable)
	void PressButton();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//UInteractionComponent
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	void InteractionRequested() override;

	//called internally when the button has been pressed
	void OnButtonPressed();

	UFUNCTION(BlueprintCallable)
	bool IsPressed() { return ButtonState == EButtonState::BS_In; }

	void DebugDraw();
	static void OnDebugToggled(IConsoleVariable* Var);

	UPROPERTY(EditAnywhere)
	float TimeToRelease = 1.0f;

	float CurrentPressedTime = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	EButtonState ButtonState;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;

	UPROPERTY()
	UTextRenderComponent* TextRenderComponent = nullptr;
};