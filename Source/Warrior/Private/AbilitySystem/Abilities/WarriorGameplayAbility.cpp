// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo,
                                            const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	// 이 어빌리티의 활성화 정책이 'OnGiven' (즉, 어빌리티가 부여되는 즉시 활성화)으로 설정되어 있다면.
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		// 액터 정보가 유효하고, 현재 이 어빌리티가 활성화 상태가 아니라면.
		if (ActorInfo && !Spec.IsActive())
		{
			// 어빌리티 시스템 컴포넌트를 통해 이 어빌리티를 활성화하려고 시도.
			// Spec.Handle은 이 어빌리티의 고유한 식별자
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	// 이 어빌리티의 활성화 정책이 'OnGiven'으로 설정되어 있다면.
	if (AbilityActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		// 액터 정보가 유효하면.
		if (ActorInfo)
		{
			// 어빌리티 시스템 컴포넌트를 통해 이 어빌리티를 제거.
			// 이는 'OnGiven' 정책으로 활성화된 어빌리티가 종료될 때 자동으로 제거되도록 하는 것.
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnComponentFromActorInfo() const
{
	// 액터 정보에서 아바타 액터를 가져와, 해당 액터에서 UPawnCombatComponent 타입의 컴포넌트를 찾아 반환함.
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWarriorAbilitySystemComponent* UWarriorGameplayAbility::GetWarriorAbilitySystemComponentFromActorInfo() const
{
	// 현재 액터 정보에 있는 어빌리티 시스템 컴포넌트를 UWarriorAbilitySystemComponent 타입으로 캐스팅하여 반환함.
	return Cast<UWarriorAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}
