

#pragma once

#include "CoreMinimal.h"
#include "InteractionComponent.h"
#include "Curves/CurveFloat.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;
class IConsoleVariable;

UENUM()
enum class EDoorState
{
	DS_Closing = 0	UMETA(DisplayName = "Closing"),
	DS_Closed = 1	UMETA(DisplayName = "Closed"),
	DS_Opening = 2	UMETA(DisplayName = "Opening"),
	DS_Open = 3		UMETA(DisplayName = "Open"),
	DS_Locked = 4	UMETA(DisplayName = "Locked")
};

UENUM()
enum class EDoorSwing
{
	Swing_In = 0	UMETA(DisplayName = "In"),
	Swing_Out = 1	UMETA(DisplayName = "Out")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ABSTRACTION_API UDoorInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	static void OnDebugToggled(IConsoleVariable* Var);

	FRotator GetDoorSwing(APawn* pawn);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//binded to interaction input from player
	void InteractionStart() override;

	//request to open the door
	UFUNCTION(BlueprintCallable)
	void OpenDoor();

	//called internally when door has finished opening
	void OnDoorOpened();

	//request to close the door
	UFUNCTION(BlueprintCallable)
	void CloseDoor();

	//called internally when door has finished Closing
	void OnDoorClosed();

	UFUNCTION(BlueprintCallable)
	bool IsOpen() { return DoorState == EDoorState::DS_Open; }

	UFUNCTION(BlueprintCallable)
	bool IsClosed() { return DoorState == EDoorState::DS_Closed; }

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

	UPROPERTY(BlueprintReadOnly)
	EDoorState DoorState;

	UPROPERTY(BlueprintReadOnly)
	EDoorSwing DoorSwing;
};
