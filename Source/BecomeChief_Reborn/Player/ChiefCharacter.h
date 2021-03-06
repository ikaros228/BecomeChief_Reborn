// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Containers/EnumAsByte.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "ChiefCharacter.generated.h"

//Enum first
UENUM(BlueprintType)
namespace EMovementState {
	enum Type {
		Forward		UMETA(DisplayName = "Moving Forward"),
		Backward	UMETA(DisplayName = "Moving Backward"),
		Right		UMETA(DisplayName = "Moving Right"),
		Left		UMETA(DisplayName = "Moving Left"),
		FR			UMETA(DisplayName = "Moving Forward-Right"),
		FL			UMETA(DisplayName = "Moving Forward-Left"),
		BR			UMETA(DisplayName = "Moving Backward-Right"),
		BL			UMETA(DisplayName = "Moving Backward-Left"),
		EMPTY		UMETA(DisplayName = "Empty State")
	};
}

UCLASS()
class BECOMECHIEF_REBORN_API AChiefCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AChiefCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		class USpringArmComponent* cameraSpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera")
		class UCameraComponent* mainPlayerCamera;



	//LOCOMOTION--------------------------------------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float walkSpeed = 600.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		float runSpeed = 1000.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		bool bIsSprinting;

	//Locomotion helpers
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Locomotion")
		bool bForward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Locomotion")
		bool bBackward;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Locomotion")
		bool bRight;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Locomotion")
		bool bLeft;

	//Locomotion functions
	UFUNCTION(BlueprintCallable, Category = "Movement|Locomotion")
		void SetMovementDirection(bool isXOrientMovement, float axisValue);
	UFUNCTION(BlueprintCallable, Category = "Movement|Locomotion")
		void UpdateMovementDirection();

	//Locomotion Enum to know in which direction we are moving
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement|Locomotion")
		TEnumAsByte<EMovementState::Type> MovementEnum;
	//-------------------------------------------------------------------------------

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/* Called for forwards/backward input */
	void MoveForward(float Value);

	/* Called for side to side input */
	void MoveRight(float Value);

	void Sprint();

	void EndSprint();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Setup input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
