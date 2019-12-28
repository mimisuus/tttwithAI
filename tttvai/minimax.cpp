#include "minimax.h"
#include "logic.h"

#include <array>

int minimax::getMove(std::array<int, 9>& board) {
	if (checkWin(board) == 0) {
		int bestScore = std::numeric_limits<int>::min();
		int optMove;
		for (int i = 0; i < board.size(); i++) {
			std::array<int, 9> newBoard = board;
			if (newBoard[i] == 0) {
				newBoard[i] = 2;
				int score = nextMove(newBoard, 0, 0);
				newBoard[i] = 0;
				if (score > bestScore) {
					bestScore = score;
					optMove = i;
				}
			}
		}
		board[optMove] = 2;
		return optMove;
	}
	else {
		return -1;
	}
}


int minimax::nextMove(std::array<int, 9>& board, int max /*maximizing(1) or minimizing(0) move*/, int depth) {
	int score = checkWin(board);
	if (score != 0) {
		return (max == 1) ? weight(score) - depth: weight(score) + depth;
	}
	// minimizing player wants the lowest score possible, maximizing the highest.
	int bestScore = (max == 1) ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();

	for (int i = 0; i < board.size(); i++) {
		if (board[i] == 0) {
			board[i] = (1*(max) + 1);
			int score = nextMove(board, (max ^ 1), depth + 1); // XOR to flip it each iteration
			board[i] = 0;
			if (max == 1) {
				if (bestScore < score) bestScore = score;
			}
			else {
				if (bestScore > score) bestScore = score;
			}
		}
	}
	return bestScore;
}

int minimax::weight(int result) {
	switch (result) {
		case 1:		// lost
			return -10;
			break;
		case 2:		// won 
			return 10;
			break;
		case 3:		// tie
			return 0;
			break;
	}
}