// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

// 주어진 액터에서 WarriorAbilitySystemComponent를 가져오는 함수 구현
UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
    check(InActor); // 액터가 유효한지 확인. 유효하지 않으면 크래시 발생

    // UAbilitySystemBlueprintLibrary를 통해 액터의 어빌리티 시스템 컴포넌트를 가져와 WarriorAbilitySystemComponent로 안전하게 캐스팅하여 반환
    return CastChecked<UWarriorAbilitySystemComponent>(
       UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

// 주어진 액터에 태그가 없으면 추가하는 함수 구현
void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
    UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor); // 액터에서 어빌리티 시스템 컴포넌트(ASC)를 가져옴
    if (!ASC->HasMatchingGameplayTag(TagToAdd)) // ASC가 해당 태그를 가지고 있지 않으면
    {
       ASC->AddLooseGameplayTag(TagToAdd); // ASC에 해당 태그를 추가함 (느슨한 태그)
    }
}

// 주어진 액터에 태그가 있으면 제거하는 함수 구현
void UWarriorFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
    UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor); // 액터에서 어빌리티 시스템 컴포넌트(ASC)를 가져옴

    if (ASC->HasMatchingGameplayTag(TagToRemove)) // ASC가 해당 태그를 가지고 있으면
    {
       ASC->RemoveLooseGameplayTag(TagToRemove); // ASC에서 해당 태그를 제거함 (느슨한 태그)
    }
}

// 주어진 액터가 태그를 가지고 있는지 확인하는 함수 구현
bool UWarriorFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
    UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor); // 액터에서 어빌리티 시스템 컴포넌트(ASC)를 가져옴

    return ASC->HasMatchingGameplayTag(TagToCheck); // ASC가 해당 태그를 가지고 있는지 확인하여 반환
}

// 주어진 액터가 태그를 가지고 있는지 확인하고, 결과에 따라 블루프린트 실행 핀을 제어하는 함수 구현
void UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck,
                                                  EWarriorConfirmType& OutConfirmType)
{
    // NativeDoesActorHaveTag 함수의 결과에 따라 OutConfirmType을 Yes 또는 No로 설정
    OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;
}