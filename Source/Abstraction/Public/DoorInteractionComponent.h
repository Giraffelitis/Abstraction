#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABSTRACTION_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	FRotator DesiredRotation = FRotator::ZeroRotator;

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;
	FRotator CloseRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere)
	float TimeToRotate = 1.0f;

	float CurrentRotationTime = 0.0f;

	UPROPERTY(EditAnywhere)
		ATriggerBox* TriggerBox;

	UPROPERTY(EditAnywhere)
		FRuntimeFloatCurve OpenCurve;

	UPROPERTY(EditAnywhere)
		FRuntimeFloatCurve CloseCurve;

};
