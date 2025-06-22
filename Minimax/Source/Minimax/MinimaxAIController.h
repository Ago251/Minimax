// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/Button.h"
#include "Containers/Array.h"
#include "MinimaxAIController.generated.h"

/**
 * 
 */
class UTextBlock;
class ABasePlayer;

UCLASS()
class MINIMAX_API AMinimaxAIController : public AAIController
{
	GENERATED_BODY()

private:
	ABasePlayer* currentPlayer;

private:
	int32 MiniMax(TArray<FString> Grid, int32 depth, int32 a, int32 b, bool isMaximizer);

	bool IsWinner(TArray<FString> Grid, FString player);

	int32 Evaluate(TArray<FString> Grid, int32 depth);
	
	void BestMove(TArray<FString>Grid);

	bool IsFullGrid(TArray<FString>Grid);

	virtual void OnPossess(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
