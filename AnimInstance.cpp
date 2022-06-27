#include "CharacterAnimInstance.h"
#include "MyProject8Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UCharacterAnimInstance::NativeInitializeAnimation() 
{
	Super::NativeInitializeAnimation();

	Character = Cast<AMyCharacter>(TryGetPawnOwner());
}

void UCharacterAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
	if (Character == nullptr)
	{
		Character = Cast<AMyCharacter>(TryGetPawnOwner());
	}

	if (Character)
	{
		//Get the lateral speed of the character from velocity
		FVector Velocity{ Character->GetVelocity() };
		Velocity.Z = 0;
		Speed = Velocity.Size();

		//Is the character in the air?
		bIsInAir = Character->GetCharacterMovement()->IsFalling();

		//Is the Character accelerating?
		if (Character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bAcceleration = true;
		}
		else
		{
			bAcceleration = false;
		}

		FRotator AimRotation = Character->GetBaseAimRotation();
		FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(Character->GetVelocity());
		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;

		if (Character->GetVelocity().Size() > 0.f)
		{
			LastMovementOffsetYaw = MovementOffsetYaw;
		}
	}
}
