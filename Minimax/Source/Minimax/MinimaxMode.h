// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePlayer.h"
#include "GameFramework/GameModeBase.h"
#include "MinimaxMode.generated.h"

/**
 * 
 */
UCLASS()
class MINIMAX_API AMinimaxMode : public AGameModeBase
{
	GENERATED_BODY()
	
private:
	int currentPlayer = 0;
	ABasePlayer* players[2];
	TArray<UButton*> CurrentGrid;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	ABasePlayer* GetPlayer(int32 index, FString icon);

public:
	UFUNCTION(BlueprintCallable, Category = "MyCategory")
	void StartGame(TArray<UButton*> Grid);

	void PlayerTurnEnd(int32 index);
};
