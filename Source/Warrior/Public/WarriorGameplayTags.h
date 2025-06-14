// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace WarriorGameplayTags
{
	/* Input Tags */
	// WARRIOR_API : 해당 클래스나 함수가 모듈 외부로 공개
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move); // InputTag_Move 게임플레이 태그를 외부에 선언.
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look); // InputTag_Look 게임플레이 태그를 외부에 선언.
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);

	/* Player Tags */
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unquip_Axe);
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
}