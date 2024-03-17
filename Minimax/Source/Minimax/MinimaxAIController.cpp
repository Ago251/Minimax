// Fill out your copyright notice in the Description page of Project Settings.


#include "MinimaxAIController.h"


int32 AMinimaxAIController::MiniMax(TArray<UButton*>& Grid, int32 depth, ABasePlayer* player) {
    int32 score = 0;

    for (int i = 0; i < Grid.Num(); ++i)
    {
        UButton* CurrentButton = Grid[i];
        // Esegui operazioni sul button corrente...
    }

    return score;
}

bool AMinimaxAIController::IsWinner(TArray<UButton*>& Grid, ABasePlayer* player) {
    //Horizontal
    for (int i = 0; i < 7; i += 3)
    {
        if (GetText(Grid[i])->GetLabelText().ToString() == player->Icon && GetText(Grid[i + 1])->GetLabelText().ToString() == player->Icon && GetText(Grid[i + 2])->GetLabelText().ToString() == player->Icon)
            return true;
    }


    //Vertical
    for (int i = 0; i < 3; ++i)
    {
        if (GetText(Grid[i])->GetLabelText().ToString() == player->Icon && GetText(Grid[i + 3])->GetLabelText().ToString() == player->Icon && GetText(Grid[i + 6])->GetLabelText().ToString() == player->Icon)
            return true;
    }

    //Diagnonal
    if (GetText(Grid[0])->GetLabelText().ToString() == player->Icon && GetText(Grid[4])->GetLabelText().ToString() == player->Icon && GetText(Grid[8])->GetLabelText().ToString() == player->Icon ||
        GetText(Grid[2])->GetLabelText().ToString() == player->Icon && GetText(Grid[4])->GetLabelText().ToString() == player->Icon && GetText(Grid[6])->GetLabelText().ToString() == player->Icon)
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
