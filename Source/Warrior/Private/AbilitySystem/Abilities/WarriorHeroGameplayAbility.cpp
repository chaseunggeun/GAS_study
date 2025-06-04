// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"

#include "Characters/WarriorHeroCharacter.h"
#include "Controllers/WarriorHeroController.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if (!CashedWarriorHeroCharacter.IsValid()) // 캐시된 영웅 캐릭터가 유효하지 않으면.
	{
		CashedWarriorHeroCharacter = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor); // 현재 액터 정보에서 아바타 액터를 영웅 캐릭터로 캐스팅하여 캐시.
	}

	// 캐시된 영웅 캐릭터가 유효하면 해당 포인터를 반환하고, 아니면 nullptr 반환.
	return CashedWarriorHeroCharacter.IsValid() ? CashedWarriorHeroCharacter.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if (!CashedWarriorHeroController.IsValid()) // 캐시된 영웅 컨트롤러가 유효하지 않으면.
	{
		CashedWarriorHeroController = Cast<AWarriorHeroController>(CurrentActorInfo->PlayerController); // 현재 액터 정보에서 플레이어 컨트롤러를 영웅 컨트롤러로 캐스팅하여 캐시.
	}

	// 캐시된 영웅 컨트롤러가 유효하면 해당 포인터를 반환하고, 아니면 nullptr 반환.
	return CashedWarriorHeroController.IsValid() ? CashedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	// 영웅 캐릭터를 가져와서 해당 캐릭터의 전투 컴포넌트를 반환.
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}