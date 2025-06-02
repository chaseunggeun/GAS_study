// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
															  int32 ApplyLevel)
{
	check(InASCToGive);

	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel); // 'OnGiven' 시 활성화되는 어빌리티들을 부여.
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel); // 반응형 어빌리티들을 부여.
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive,
	UWarriorAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty()) // 부여할 어빌리티 배열이 비어있으면.
	{
		return;
	}
	for (const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive) // 각 어빌리티 클래스에 대해 반복.
	{
		if (!Ability) continue;; // 어빌리티가 유효하지 않으면 다음으로 넘어감.

		FGameplayAbilitySpec AbilitySpec(Ability); // 어빌리티 클래스로부터 어빌리티 스펙(Spec)을 생성함.
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); // 어빌리티의 소스 오브젝트를 어빌리티 시스템 컴포넌트의 아바타 액터로 설정함.
		AbilitySpec.Level = ApplyLevel; // 어빌리티의 레벨을 설정함.
       
		InASCToGive->GiveAbility(AbilitySpec); // 어빌리티 시스템 컴포넌트에 이 어빌리티 스펙을 부여함.
	}
}