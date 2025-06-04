// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WARRIOR_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	template<class T>
	T* GetOwningPawn() const // 이 컴포넌트를 소유한 폰(Pawn)을 가져오는 함수
	{
		// 'T'가 APawn으로부터 파생된 클래스인지 컴파일 시점에 확인. 아니면 에러 발생
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter to GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner()); // 컴포넌트의 오너(Actor)를 T 타입의 폰으로 안전하게 캐스팅하여 반환
	}

	APawn* GetOwningPawn() const // 오버로드된 GetOwningPawn 함수 (템플릿이 아닌 APawn 타입 반환)
	{
		return GetOwningPawn<APawn>(); // 템플릿 함수를 호출하여 APawn 타입의 소유 폰을 가져옴
	}

	template<class T> // 템플릿 함수 선언
	T* GetOwningController() const // 이 컴포넌트를 소유한 컨트롤러를 가져오는 함수
	{
		// 'T'가 AController로부터 파생된 클래스인지 컴파일 시점에 확인
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter to GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>(); // 소유 폰을 가져와서 그 폰의 컨트롤러를 T 타입으로 가져옴
	}
};
