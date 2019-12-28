#include <array>

int checkWin(std::array<int, 9> board) {
	int winner = 0; // 0,1,2,3 = ongoing,player1,player2,tie
	int p; // player

	for (p = 1; (p <= 2) && (winner == 0); p++) {
		for (int i = 0; i <= 2; i++) {
			if (board[i] == p && board[i + 3] == p && board[i + 6] == p) // vertical win conditions
				winner = p;
			else if (board[i * 3] == p && board[i * 3 + 1] == p && board[i * 3 + 2] == p) // horizontal win conditions
				winner = p;
		}
		if ((board[0] == p && board[4] == p && board[8] == p) || (board[2] == p && board[4] == p && board[6] == p)) // diagonal win conditions
			winner = p;
	}
	// game is tied if no squares are empty, and game is still going
	if (winner == 0) {
		winner = 3; // tie until stated otherwise
		for (int i = 0; i < 9; i++) {
			if (board[i] == 0) {
				winner = 0;
			}
		}
	}
	return winner;
}