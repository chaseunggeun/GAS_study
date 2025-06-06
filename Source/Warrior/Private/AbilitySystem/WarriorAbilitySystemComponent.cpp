// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UWarriorAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid())
	{
		return;
	}

	// 현재 활성화 가능한 모든 어빌리티 스펙들을 순회함
	for (const FGameplayAbilitySpec& AbilitySpec :GetActivatableAbilities())
	{
		// 현재 어빌리티 스펙의 동적 어빌리티 태그에 전달받은 입력 태그가 정확히 포함되어 있지 않으면 다음 어빌리티로 건너뜀
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		// 해당 입력 태그를 가진 어빌리티 스펙을 활성화하려고 시도함
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UWarriorAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
}
