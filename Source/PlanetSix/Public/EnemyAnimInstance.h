// This work is the sole property of 2Pow6 Games.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PLANETSIX_API UEnemyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()


public:
     
    UPROPERTY(BlueprintReadWrite)
        bool bIsShooting; 
    
    UPROPERTY(BlueprintReadWrite)
        FRotator RotationToAim;
};
