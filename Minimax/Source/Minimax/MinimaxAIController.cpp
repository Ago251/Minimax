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
	if (currentPlayer != nullptr && currentPlayer->isYourTurn) {
		BestMove(*currentPlayer->CurrentGrid);
		currentPlayer->EndTurn(*currentPlayer->CurrentGrid);
	}
}


void AMinimaxAIController::StartTurn(TArray<UButton*> Grid) {
	BestMove(Grid);
}

void AMinimaxAIController::BestMove(TArray<UButton*>& Grid) {
	int bestScore = std::numeric_limits<int>::min();
	int bestMoveIndex = 0;
	TArray<FString> stringGrid = CreateStringArray(Grid);

	for (int i = 0; i < 9; ++i) {
			if (stringGrid[i].IsEmpty()){
				stringGrid[i] = "O";
				int score = MiniMax(stringGrid, 0, false);
				stringGrid[i] = "";
				if (score > bestScore) {
					bestScore = score;
					bestMoveIndex = i;
				}
			}
	}

	if(bestMoveIndex != 0)
		GetText(Grid[bestMoveIndex])->SetText(FText::FromString("O"));
}

TArray<FString> AMinimaxAIController::CreateStringArray(TArray<UButton*>& Grid) {
	TArray<FString> stringGrid;
	stringGrid.SetNum(9);

	for (int i = 1; i < 9; ++i) {
		stringGrid[i] = GetText(Grid[i])->GetText().ToString();
	}

	stringGrid[0] = "X";

	return stringGrid;
}

int32 AMinimaxAIController::MiniMax(TArray<FString>& Grid, int32 depth, bool isMaximizer) {
	int32 score = Evaluate(Grid);

	if (score != 0 || depth == 9)
		return score;

	for (int i = 1; i < 9; ++i)
	{
		int bestScore = isMaximizer ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
		if (Grid[i].IsEmpty()) {
			Grid[i] = isMaximizer ? "O" : "X";
			score = isMaximizer ? std::max(bestScore, MiniMax(Grid, depth, !isMaximizer)) : std::min(bestScore, MiniMax(Grid, depth, !isMaximizer));
			Grid[i] = "";
		}

		return bestScore;
	}

	return - 1;
}

int32 AMinimaxAIController::Evaluate(TArray<FString>& Grid) {
	if (IsWinner(Grid, "O"))
		return 1; // Vittoria per il giocatore 1
	else if (IsWinner(Grid, "X"))
		return -1; // Vittoria per il giocatore 2
	else
		return 0;
}

bool AMinimaxAIController::IsWinner(TArray<FString>& Grid, FString player) {
	//Horizontal
	for (int i = 0; i < 7; i += 3)
	{
		if (Grid[i] == player && Grid[i + 1] == player && Grid[i + 2]== player)
			return true;
	}


	//Vertical
	for (int i = 0; i < 3; ++i)
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

UTextBlock* AMinimaxAIController::GetText(UButton* Button)
{
	if (Button)
	{
		// Ottieni il componente figlio TextBlock direttamente
		UTextBlock* TextBlock = Cast<UTextBlock>(Button->GetChildAt(0));
		return TextBlock;
	}

	// Se il Button ? nullo o non ha un TextBlock come figlio, restituisci nullptr
	return nullptr;
}
