//Only code that pertains to flying is included

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS(config=Game)
class AMyProject8Character : public ACharacter
{
	GENERATED_BODY()
	
public:
	AMyProject8Character();
	
protected:
	void Flying();
	void StopFlying();	
	void LiftInAir();
	
	float RunningSpeed; 
	int32 JumpCounter;
	float JumpHeight;
}
