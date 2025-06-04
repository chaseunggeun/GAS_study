// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"

// #include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorDebugHelper.h"
#include "Items/Weapons/WarriorWeaponBase.h"

// 생성된 무기를 등록하는 함수
void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	// 이미 등록된 무기 태그인지 확인. 등록되어 있다면 오류 발생.
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("A named %s has already been added as carried weapon"), *InWeaponTagToRegister.ToString());
	check(InWeaponToRegister); // 등록할 무기가 유효한지 확인.

	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister); // 무기 태그와 함께 무기를 맵에 추가함.

	if (bRegisterAsEquippedWeapon) // 장착된 무기로 등록할지 여부 확인.
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister; // 현재 장착된 무기 태그를 설정함.
	}

	const FString WeaponString = FString::Printf(TEXT("A weapon named: %s has been registered using the tag %s"),*InWeaponToRegister->GetName(), *InWeaponTagToRegister.ToString());
	Debug::Print(WeaponString);
}

// 태그로 캐릭터가 소지한 무기를 가져오는 함수
AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if (CharacterCarriedWeaponMap.Contains(InWeaponTagToGet)) // 맵에 해당 무기 태그가 포함되어 있는지 확인.
	{
		if (AWarriorWeaponBase* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet)) // 태그로 무기를 찾음.
		{
			return *FoundWeapon; // 찾은 무기를 반환함.
		}
	}
    
	return nullptr; // 무기를 찾지 못하면 nullptr 반환함.
}

// 현재 장착된 무기를 가져오는 함수
AWarriorWeaponBase* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) // 현재 장착된 무기 태그가 유효하지 않으면.
	{
		return nullptr; // nullptr 반환함.
	}

	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag); // 현재 장착된 무기 태그로 무기를 찾아 반환함.
}
