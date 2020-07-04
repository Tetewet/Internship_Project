// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuestActor.h"
#include "NPC.generated.h"

class UBoxComponent;
class UTextRenderComponent;
class USkeletalMeshComponent;



UCLASS()
class PLANETSIX_API ANPC : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ANPC();

	UPROPERTY(EditAnywhere)
		UBoxComponent* boxcomponent;

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* textrenderInteraction;

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* textrenderQuest;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* skeleton;

	UPROPERTY(EditAnywhere)
		UAnimationAsset* AnimIdle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		FName QuestID;
	UPROPERTY(EditAnywhere)
		UAnimationAsset* AnimInteract;

	bool bOnInteraction;

	UPROPERTY(BlueprintReadWrite)
		FQuestData NPCQuest;

	//The Component of the data table to be able to be read in Unreal
	FQuestData* QuestDataPointer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
		class UDataTable* QuestDatatable;

	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	

};
