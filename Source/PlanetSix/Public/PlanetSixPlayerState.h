// This work is the sole property of 2Pow6 Games.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PlanetSixCharacter.h"
#include "PlanetSixPlayerState.generated.h"

/**
 *
 */
UCLASS()
class PLANETSIX_API APlanetSixPlayerState : public APlayerState
{
	GENERATED_BODY()


public:
	//Player Stats
	UPROPERTY(Replicated)
	FPlayerInfo PlayerInfo;

	UFUNCTION(BlueprintCallable, Server, Reliable)
		void ChangeInfo(const FPlayerInfo& info);
	void ChangeInfo_Implementation(const FPlayerInfo& name);

	UFUNCTION(BlueprintCallable)
		FPlayerInfo GetInfo();

	// Used to copy properties from the current PlayerState to the passed one
	virtual void CopyProperties(class APlayerState* PlayerState) override;
	// Used to override the current PlayerState with the properties of the passed one
	virtual void OverrideWith(class APlayerState* PlayerState) override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	virtual void BeginPlay() override;

	void ReloadPlayerInfo();
	



};
