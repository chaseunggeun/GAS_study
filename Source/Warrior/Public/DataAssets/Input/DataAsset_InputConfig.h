// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputAction* InputAction;

	bool IsValid() const
	{
		return InputTag.IsValid() && InputAction;
	}
};
/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext; // 기본 입력 매핑 컨텍스트 변수 선언.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarriorInputActionConfig> NativeInputActions; // 네이티브 입력 액션 설정들을 담는 배열 선언.

	UInputAction* FindNativeInputActionByTag(const FGameplayTag InInputTag) const; // 주어진 태그로 네이티브 입력 액션을 찾아 반환하는 함수 선언.

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (TitleProperty = "InputTag"))
	TArray<FWarriorInputActionConfig> AbilityInputActions; 
};