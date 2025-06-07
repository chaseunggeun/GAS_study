// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/DataAsset_HeroStartUpData.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"


void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	// HeroStartUpAbilitySets 배열에 있는 각 영웅 어빌리티 세트에 대해 반복.
	for (const FWarriorHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant); // 부여할 어빌리티 클래스로부터 어빌리티 스펙(Spec)을 생성.
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor(); // 어빌리티의 소스 오브젝트를 어빌리티 시스템 컴포넌트의 아바타 액터로 설정.
		AbilitySpec.Level = ApplyLevel; // 어빌리티의 레벨을 ApplyLevel로 설정.
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag); // 어빌리티 스펙에 동적으로 입력 태그를 추가.
       
		InASCToGive->GiveAbility(AbilitySpec); // 어빌리티 시스템 컴포넌트에 이 어빌리티 스펙을 부여.
	}
}