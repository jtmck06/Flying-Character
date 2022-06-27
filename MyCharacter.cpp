//The code that is presented is only relevant to making a character fly any preset or code is not included 

#include "MyCharacter.h"

AMyProject8Character::AMyProject8Character(): RunningSpeed(650.f), JumpHeight(650.f)
{
  	GetCharacterMovement()->MaxWalkSpeed = RunningSpeed;
	GetCharacterMovement()->MaxFlySpeed = RunningSpeed;
}

void AMyProject8Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Character Movement
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyProject8Character::JumpButtonPressed);
  PlayerInputComponent->BindAction("Fly", IE_Released, this, &AMyProject8Character::Flying);
	PlayerInputComponent->BindAction("StopFlying", IE_Pressed, this, &AMyProject8Character::StopFlying);
	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AMyProject8Character::Dashing);
}

void AMyProject8Character::JumpButtonPressed()
{
	Jump();
	++JumpCounter;
}

void AMyProject8Character::Jump()
{
	/*if (JumpCtr == 0)
	{
		ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, false);
	}*/

	if (GetCharacterMovement()->IsFalling() || GetCharacterMovement()->IsFlying())
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		if (JumpCounter == 3)
		{
			StopFlying();
		}
	}
	else {
		ACharacter::LaunchCharacter(FVector(0, 0, JumpHeight), false, false);
	}
}

void AMyProject8Character::Landed(const FHitResult& Hit)
{
	JumpCounter = 0;
	//Resets jumps once character lands 
}

void AMyProject8Character::Flying() 
{
	if (EMovementMode::MOVE_Walking)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		LiftInAir();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Im Flying!!"));
	}
	else if (EMovementMode::MOVE_Flying) {
		AddMovementInput(GetActorUpVector(), 800);
	}
}

void AMyProject8Character::LiftInAir()
{
	const FVector UpVector = this->GetActorUpVector().UpVector;
	ACharacter::LaunchCharacter(FVector(0, 0, 1200), false, false);

}

void AMyProject8Character::StopFlying() 
{
	if (EMovementMode::MOVE_Flying)
	{
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("Not Flying!!"));
	}
}
