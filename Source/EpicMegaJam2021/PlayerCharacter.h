// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DamageInterface.h"
#include "PlayerCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthUpdated, float, HealthValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMemoryUpdated, float, MemoryValue);

UCLASS()
class EPICMEGAJAM2021_API APlayerCharacter : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable)
		FOnHealthUpdated OnHealthUpdated;

	UPROPERTY(BlueprintAssignable)
		FOnMemoryUpdated OnMemoryUpdated;

	void MoveHorizontal(float inputValue);

	void MoveVertical(float inputValue);

	void ActionPressed();

	void Shoot();
	UFUNCTION(Category=FPSCharacter, BlueprintCallable)
	struct FHitResult GetRaycastHit(float rayDistance, bool& didHit);

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComponent;

	void ReceiveDamage(int damage);
};
