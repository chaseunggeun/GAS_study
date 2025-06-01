// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag InInputTag) const
{
	for (const FWarriorInputActionConfig& InputActionConfig : NativeInputActions) // 모든 입력 액션 설정에서
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction) // 태그가 일치하고 액션이 유효하면
		{
			return InputActionConfig.InputAction; // 해당 입력 액션 리턴
		}
	}
	return nullptr;
}