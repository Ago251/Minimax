# 🎮 Tic-Tac-Toe with Minimax

This project implements a **Tic-Tac-Toe game** using **Unreal Engine** with a fully functional AI opponent based on the **Minimax algorithm** enhanced by **Alpha-Beta pruning**.
The game features a playable **User Interface (UI)** that allows a human player to face off against a perfect AI opponent, demonstrating core concepts in adversarial search and decision-making in games.

## 🧠 Core AI Logic

- **Minimax Algorithm**: The AI evaluates all possible game states recursively to determine the best move, assuming optimal play from both sides.
- **Alpha-Beta Pruning**: Integrated into the Minimax loop to cut off unnecessary branches and improve performance.
- **Evaluation Function**: Simple scoring system (+100 for AI win, -100 for player win, 0 otherwise).
- **Move Selection**: AI plays optimally by choosing the move with the highest score during its turn.
