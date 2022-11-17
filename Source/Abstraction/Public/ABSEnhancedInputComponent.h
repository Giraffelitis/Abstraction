#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "ABSInputConfig.h"
#include "GameplayTagContainer.h"
#include "ABSEnhancedInputComponent.generated.h"

/**
 *	Header only nothing added to .cpp
 *	Creates template to be used in other files as a method to Bind Actions using GameplayTags
 */

UCLASS()
class ABSTRACTION_API UABSEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserClass, typename FuncType>
	void BindActionByTag(const UABSInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func);
};

template<class UserClass, typename FuncType>
void UABSEnhancedInputComponent::BindActionByTag(const UABSInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func)
{
	check(InputConfig);
	if (const UInputAction* IA = InputConfig->FindInputActionForTag(InputTag))
	{
		BindAction(IA, TriggerEvent, Object, Func);
	}
}