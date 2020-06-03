// Fill out your copyright notice in the Description page of Project Settings.


#include "ChiefCharacter.h"

// Sets default values
AChiefCharacter::AChiefCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	cameraSpringArm->SetupAttachment(GetMesh(), "head");
	cameraSpringArm->TargetArmLength = 0.f;

	mainPlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Main Camera"));
	mainPlayerCamera->SetupAttachment(cameraSpringArm);
	
}

void AChiefCharacter::SetMovementDirection(bool isXOrientMovement, float axisValue)
{
	if (isXOrientMovement)
	{
		if (axisValue == 0.0f)
		{
			bRight = false;
			bLeft = false;
		}
		else
		{
			bRight = axisValue > 0.0f;
			bLeft = axisValue < 0.0f;
		}
	}
	else
	{
		if (axisValue == 0.0f)
		{
			bForward = false;
			bBackward = false;
		}
		else
		{
			bForward = axisValue > 0.0f;
			bBackward = axisValue < 0.0f;
		}
	}
}

void AChiefCharacter::UpdateMovementDirection()
{
	if (bForward)
	{
		if (bRight)
			MovementEnum = EMovementState::FR;
		else
		{
			if (bLeft)
				MovementEnum = EMovementState::FL;
			else
				MovementEnum = EMovementState::Forward;
		}
	}
	else
	{
		if (bBackward)
		{
			if (bRight)
				MovementEnum = EMovementState::BR;
			else
			{
				if (bLeft)
					MovementEnum = EMovementState::BL;
				else
					MovementEnum = EMovementState::Backward;
			}
		}
		else
		{
			if (bRight)
				MovementEnum = EMovementState::Right;
			else if (bLeft)
				MovementEnum = EMovementState::Left;
		}
	}
}

// Called when the game starts or when spawned
void AChiefCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AChiefCharacter::MoveForward(float Value)
{
	if ((Controller != NULL))
	{
		SetMovementDirection(false, Value);
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AChiefCharacter::MoveRight(float Value)
{
	if ((Controller != NULL))
	{
		SetMovementDirection(true, Value);
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AChiefCharacter::Sprint()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->MaxWalkSpeed = runSpeed;
		bIsSprinting = true;
	}
}

void AChiefCharacter::EndSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	bIsSprinting = false;
}

// Called every frame
void AChiefCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMovementDirection();
}

// Called to bind functionality to input
void AChiefCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AChiefCharacter::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AChiefCharacter::EndSprint);

	PlayerInputComponent->BindAxis("MoveForward", this, &AChiefCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AChiefCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

}

