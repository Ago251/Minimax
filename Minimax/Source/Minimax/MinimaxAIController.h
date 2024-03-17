// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Components/Button.h"
#include "Containers/Array.h"
#include "BasePlayer.h"
#include "MinimaxAIController.generated.h"

/**
 * 
 */
class UTextBlock;

UCLASS()
class MINIMAX_API AMinimaxAIController : public AAIController
{
	GENERATED_BODY()

private:
	int32 MiniMax(TArray<FString> Grid, int32 depth, ABasePlayer* player, bool isMaximizer);

	bool IsWinner(TArray<FString> Grid, FString player);

	UTextBlock* GetText(UButton* Button);

	int32 Evaluate(TArray<FString> Grid, FString player, bool isMaximizer);
	
	void BestMove(TArray<UButton*>& Grid, int32 depth, ABasePlayer* player, bool isMaximizer);

	TArray<FString> CreateStringArray(TArray<UButton*>& Grid);
};
