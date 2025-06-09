// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorFunctionLibrary.generated.h"

class UWarriorAbilitySystemComponent;

UENUM() // 이 enum을 언리얼 엔진 리플렉션 시스템에 등록
enum class EWarriorConfirmType : uint8 // 확인/부정 선택지를 나타내는 enum 정의
{
	Yes, // '예'
	No   // '아니오'
};
/**
 * */
UCLASS() // 이 클래스를 언리얼 오브젝트 클래스로 선언
class WARRIOR_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary // WARRIOR 모듈 외부로 공개되는 WarriorFunctionLibrary 클래스 선언. UBlueprintFunctionLibrary를 상속
{
	GENERATED_BODY() // UCLASS에 필요한 보일러플레이트 코드 생성

public:
	// 주어진 액터에서 WarriorAbilitySystemComponent를 가져오는 네이티브 C++ 함수 선언
	static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary") // 블루프린트에서 호출 가능하며 "Warrior|FunctionLibrary" 카테고리에 표시
	// 주어진 액터에 태그가 없으면 추가하는 함수 선언
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary") // 블루프린트에서 호출 가능하며 "Warrior|FunctionLibrary" 카테고리에 표시
	// 주어진 액터에 태그가 있으면 제거하는 함수 선언
	static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	// 주어진 액터가 태그를 가지고 있는지 확인하는 네이티브 C++ 함수 선언
	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType")) // 블루프린트에서 호출 가능, "Warrior|FunctionLibrary" 카테고리, 노드 이름과 출력 핀 설정
	// 주어진 액터가 태그를 가지고 있는지 확인하고, 결과에 따라 다른 실행 핀을 제공하는 블루프린트용 함수 선언
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType);
};