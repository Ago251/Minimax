// Fill out your copyright notice in the Description page of Project Settings.

#include "MinimaxAIController.h"
#include "BasePlayer.h"
#include "Components/TextBlock.h"

void AMinimaxAIController::OnPossess(APawn* InPawn) {
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("Possesed"));
	ABasePlayer* player = Cast<ABasePlayer>(InPawn);
	if (player) {
		currentPlayer = player;
		UE_LOG(LogTemp, Warning, TEXT("Possesed player"));
	}
}

void AMinimaxAIController::Tick(float deltaTime) {
	if (currentPlayer != nullptr && currentPlayer->isYourTurn)
		BestMove(currentPlayer->CurrentGrid);
}

void AMinimaxAIController::BestMove(TArray<FString>  Grid) {
	float bestScore = -std::numeric_limits<int32>::max();
	int32 bestMoveIndex = -1;

	for (int i = 0; i < 9; ++i) {
			if (Grid[i].IsEmpty()){
				Grid[i] = "O";
				float score = MiniMax(Grid, 0, -std::numeric_limits<int32>::max(), std::numeric_limits<int32>::max(), false);
				Grid[i] = "";
				if (score > bestScore) {
					bestScore = score;
					bestMoveIndex = i;
				}
			}
	}

	if(bestMoveIndex != -1)
		currentPlayer->EndTurn(bestMoveIndex);
}

int32 AMinimaxAIController::MiniMax(TArray<FString> Grid, int32 depth, int32 a, int32 b, bool isMaximizer) {
	int32 score = Evaluate(Grid, depth);

	if (score != 0 || IsFullGrid(Grid) || depth == 9)
		return score;

	int32 bestScore = isMaximizer ? -std::numeric_limits<int32>::max() : std::numeric_limits<int32>::max();

	for (int i = 0; i < 9; ++i)
	{
		if (Grid[i].IsEmpty()) {
			Grid[i] = isMaximizer ? "O" : "X";
			bestScore = isMaximizer ? std::max(bestScore, MiniMax(Grid, depth + 1, a, b, !isMaximizer)) : std::min(bestScore, MiniMax(Grid, depth + 1, a, b, !isMaximizer));
			Grid[i] = "";
			if (isMaximizer) {
				if (bestScore >= b)
					break;
				a = std::max(a, bestScore);
			}
			else {
				if (bestScore <= a)
					break;
				b = std::min(b, bestScore);
			}
		}
	}

	return bestScore;
}

int32 AMinimaxAIController::Evaluate(TArray<FString> Grid, int32 depth) {
	if (IsWinner(Grid, "O"))
		return 100 - depth; 
	else if (IsWinner(Grid, "X"))
		return -100 + depth; 
	else
		return 0;
}

bool AMinimaxAIController::IsFullGrid(TArray<FString> Grid)
{
	for (int i = 0; i < 9; ++i)
	{
		if (Grid[i].IsEmpty())
			return false;
	}

	return true;
}


bool AMinimaxAIController::IsWinner(TArray<FString> Grid, FString player) {
	//Horizontal
	for (int i = 0; i < 7; i += 3)
	{
		if (Grid[i] == player && Grid[i + 1] == player && Grid[i + 2]== player)
			return true;
	}


	//Vertical
	for (int i = 0; i < 3; i++)
	{
		if (Grid[i] == player && Grid[i + 3] == player && Grid[i + 6] == player)
			return true;
	}

	//Diagnonal
	if (Grid[0] == player && Grid[4] == player && Grid[8] == player ||
		Grid[2] == player && Grid[4] == player && Grid[6] == player)
		return true;

	return false;
}
