// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSPlayerController.h"
#include "PlayerCharacter.h"

void AFPSPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	InputComponent->BindAxis("Horizontal", this, &AFPSPlayerController::MoveHorizontal);
	InputComponent->BindAxis("Vertical", this, &AFPSPlayerController::MoveVertical);
	InputComponent->BindAxis("MouseHorizontal", this, &AFPSPlayerController::MouseHorizontal);
	InputComponent->BindAxis("MouseVertical", this, &AFPSPlayerController::MouseVertical);

	InputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AFPSPlayerController::JumpPressed);
	InputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &AFPSPlayerController::ActionPressed);
	InputComponent->BindAction("Shoot", EInputEvent::IE_Pressed, this, &AFPSPlayerController::Shoot);
	UE_LOG(LogTemp, Warning, TEXT("setup input"));
}

void AFPSPlayerController::OnPossess(APawn* aPawn) 
{
	Super::OnPossess(aPawn);
	PlayerCharacter = Cast<APlayerCharacter>(aPawn);
	UE_LOG(LogTemp, Warning, TEXT("running onpossess"));
	if (IsValid(PlayerCharacter)) {
		UE_LOG(LogTemp, Warning, TEXT("cast success"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("cast failed"));
	}
}

void AFPSPlayerController::MoveHorizontal(float inputValue)
{
	if (IsValid(PlayerCharacter)) {
		PlayerCharacter->MoveHorizontal(inputValue);
	}
}

	void AFPSPlayerController::MoveVertical(float inputValue)
	{
		if (IsValid(PlayerCharacter)) {
			PlayerCharacter->MoveVertical(inputValue);
		}
	}

void AFPSPlayerController::MouseHorizontal(float inputValue)
{
	if (IsValid(PlayerCharacter)) 
	{
		PlayerCharacter->AddControllerYawInput(inputValue);
	}
}

void AFPSPlayerController::MouseVertical(float inputValue)
{
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->AddControllerPitchInput(inputValue);
		UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
	}
}

void AFPSPlayerController::JumpPressed()
{
	if (IsValid(PlayerCharacter)) 
	{
		PlayerCharacter->Jump();
	}
}

void AFPSPlayerController::ActionPressed()
{
	if (IsValid(PlayerCharacter)) {
		PlayerCharacter->ActionPressed();
	}
}

void AFPSPlayerController::Shoot()
{
	if (IsValid(PlayerCharacter)) {
		PlayerCharacter->Shoot();
	}
}