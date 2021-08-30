// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "InteractInterface.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	APlayerCharacter::SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	
	APlayerCharacter::CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	//CameraComponent->AttachTo(springArmComponent);
	CameraComponent->AttachToComponent(APlayerCharacter::SpringArmComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAxis("Horizontal", this, &APlayerCharacter::MoveHorizontal);
	InputComponent->BindAxis("Vertical", this, &APlayerCharacter::MoveVertical);
	InputComponent->BindAxis("MouseHorizontal", this, &APlayerCharacter::AddControllerYawInput);
	InputComponent->BindAxis("MouseVertical", this, &APlayerCharacter::AddControllerPitchInput);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);
	InputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &APlayerCharacter::ActionPressed);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &APlayerCharacter::Shoot);
}

void APlayerCharacter::MoveHorizontal(float inputValue)
{
	FRotator NewRotator = FRotator::ZeroRotator;
	NewRotator.Yaw = GetControlRotation().GetComponentForAxis(EAxis::Z);
	AddMovementInput(UKismetMathLibrary::GetRightVector(NewRotator), inputValue);

}

void APlayerCharacter::MoveVertical(float inputValue)
{
	FRotator NewRotator = FRotator::ZeroRotator;
	NewRotator.Yaw = GetControlRotation().GetComponentForAxis(EAxis::Z);
	AddMovementInput(UKismetMathLibrary::GetForwardVector(NewRotator), inputValue);
}

void APlayerCharacter::ActionPressed()
{
	bool didHit;
	FHitResult hitResult = APlayerCharacter::GetRaycastHit(200.0f, didHit);
	if (didHit)
	{
		IInteractInterface::Execute_Interact(Cast<UObject>(hitResult.Actor), this);
	}
}

void APlayerCharacter::Shoot()
{
	bool didHit;
	FHitResult hitResult = APlayerCharacter::GetRaycastHit(200.0f, didHit);
	if (didHit)
	{

	}
}

struct FHitResult APlayerCharacter::GetRaycastHit(float rayDistance, bool& didHit)
{
	FVector startVector = APlayerCharacter::CameraComponent->GetComponentLocation();
	FVector rotatedVector = APlayerCharacter::CameraComponent->GetComponentRotation().Vector() * rayDistance;
	FHitResult hitResult;
	didHit = GetWorld()->LineTraceSingleByChannel(hitResult, startVector, startVector + rotatedVector, ECC_Visibility);
	return hitResult;
}

 void APlayerCharacter::ReceiveDamage(int damage)
{

}

