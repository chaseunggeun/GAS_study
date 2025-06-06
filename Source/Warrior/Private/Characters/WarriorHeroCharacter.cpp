// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorHeroCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "Components/Input/WarriorInputComponent.h"
#include "WarriorGameplayTags.h"
#include "Components/Combat/HeroCombatComponent.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"

#include "WarriorDebugHelper.h"

AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f); // 캡슐 크기 설정
	bUseControllerRotationPitch = false; // 컨트롤러 Pitch 회전 사용 안 함
	bUseControllerRotationYaw = false; // 컨트롤러 Yaw 회전 사용 안 함
	bUseControllerRotationRoll = false; // 컨트롤러 Roll 회전 사용 안 함

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom")); // 카메라 붐 생성
	CameraBoom->SetupAttachment(GetRootComponent()); // 루트 컴포넌트에 부착
	CameraBoom->TargetArmLength = 200.f; // 팔 길이 설정
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f); // 소켓 오프셋 설정
	CameraBoom->bUsePawnControlRotation = true; // 폰 컨트롤러 회전 따름

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera")); // 팔로우 카메라 생성
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // 카메라 붐에 부착
	FollowCamera->bUsePawnControlRotation = false; // 폰 컨트롤러 회전 사용 안 함

	GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향으로 회전
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); // 회전 속도 설정
	GetCharacterMovement()->MaxWalkSpeed = 400.f; // 최대 걷기 속도 설정
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; // 걷기 중 감속도 설정

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("UHeroCombatComponent"));
}

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull()) // 캐릭터 시작 데이터가 비어있지 않으면 (유효한 데이터가 있으면).
	{
		if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.LoadSynchronous()) // 시작 데이터 에셋을 동기적으로 로드함. 로드 성공하면.
		{
			LoadedData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent); // 로드된 데이터 에셋에서 어빌리티 시스템 컴포넌트에 어빌리티를 부여함.
		}
	}
	// if (WarriorAbilitySystemComponent && WarriorAttributeSet)
	// {
	// 	const FString ASCText = FString::Printf(TEXT("Owner Actor: %s, AvatarActor: %s"), *WarriorAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *WarriorAbilitySystemComponent->GetAvatarActor()->GetActorLabel());
	// 	Debug::Print(TEXT("Ability system component valid. ") + ASCText, FColor::Green);
	// 	Debug::Print(TEXT("AttributeSet valid. ") + ASCText, FColor::Green);
	// }
	
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config")); // 입력 설정 데이터 에셋이 할당되었는지 확인.

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer(); // 로컬 플레이어 가져옴.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer); // Enhanced Input 서브시스템 가져옴.

	check(Subsystem); // 서브시스템이 유효한지 확인.

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0); // 기본 매핑 컨텍스트를 추가함.

	UWarriorInputComponent* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent); // WarriorInputComponent로 캐스팅함.

	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move); // 이동 입력 액션을 바인딩함.
	WarriorInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look); // 이동 입력 액션을 바인딩함.

	WarriorInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, & ThisClass::Input_AbilityInputReleased);
}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorHeroCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>(); // 입력 값에서 2D 이동 벡터를 가져옴.

	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); // 컨트롤러의 Yaw 회전을 기반으로 이동 회전 설정.

	if (MovementVector.Y !=0.f) // Y축 이동 값이 0이 아니면.
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector); // 전방 방향을 계산함.

		AddMovementInput(ForwardDirection, MovementVector.Y); // 전방으로 이동 입력을 추가함.
	}

	if (MovementVector.X !=0.f) // X축 이동 값이 0이 아니면.
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector); // 우측 방향을 계산함.

		AddMovementInput(RightDirection, MovementVector.X); // 우측으로 이동 입력을 추가함.
	}
}

void AWarriorHeroCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (LookAxisVector.X !=0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (LookAxisVector.Y !=0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AWarriorHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	// 워리어 어빌리티 시스템 컴포넌트의 OnAbilityInputPressed 함수를 호출해, 입력 태그를 전달함
	WarriorAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void AWarriorHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	// 워리어 어빌리티 시스템 컴포넌트의 OnAbilityInputReleased 함수를 호출해, 입력 태그를 전달함
	WarriorAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}