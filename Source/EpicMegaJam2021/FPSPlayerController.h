// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class EPICMEGAJAM2021_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void SetupInputComponent() override;

	virtual void OnPossess(APawn* aPawn) override;

public: 
	void MoveHorizontal(float inputValue);

	void MoveVertical(float inputValue);

	void MouseHorizontal(float inputValue);

	void MouseVertical(float inputValue);

	void JumpPressed();

	void ActionPressed();

	void Shoot();

	UPROPERTY(BlueprintReadOnly)
	class APlayerCharacter* PlayerCharacter;
};
