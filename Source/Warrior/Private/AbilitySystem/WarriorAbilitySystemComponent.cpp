// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

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

void UWarriorAbilitySystemComponent::GrantHeroWeaponAbilities(
	const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles)
{
	if (InDefaultWeaponAbilities.IsEmpty())
	{
		return;
	}

	for (const FWarriorHeroAbilitySet& AbilitySet : InDefaultWeaponAbilities)
	{
		if (!AbilitySet.IsValid()) continue; // 어빌리티 세트가 유효하지 않으면 건너뛰기

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant); // 부여할 어빌리티 클래스로부터 어빌리티 스펙 생성
		AbilitySpec.SourceObject = GetAvatarActor(); // 어빌리티의 소스 오브젝트를 아바타 액터로 설정
		AbilitySpec.Level = ApplyLevel; // 어빌리티 레벨 설정
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag); // 어빌리티 스펙에 입력 태그 동적으로 추가
       
		//GiveAbility(AbilitySpec); // 어빌리티 시스템 컴포넌트에 어빌리티 스펙 부여

		OutGrantedAbilitySpecHandles.AddUnique(GiveAbility(AbilitySpec)); // 부여된 어빌리티의 스펙 핸들을 출력 배열에 추가 (중복 방지)
	}
}

void UWarriorAbilitySystemComponent::RemovedGrantedHeroWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove)
{
	if (InSpecHandlesToRemove.IsEmpty())
	{
		return;
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandlesToRemove)
	{
		if (SpecHandle.IsValid())
		{
			ClearAbility(SpecHandle);
		}
	}

	InSpecHandlesToRemove.Empty();
}
