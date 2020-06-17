// This work is the sole property of 2Pow6 Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Storm.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PLANETSIX_API AStorm : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStorm();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Storm", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UBoxComponent* Collider;

	UPROPERTY(Category = "Storm", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
		UStaticMeshComponent* Mesh;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
