#ifndef minimax_h
#define minimax_h

#include <array>

class minimax {

	private:
		int nextMove(std::array<int, 9>& board, int max, int depth);
		int weight(int result);

	public:
		int getMove(std::array<int, 9>& board);
};

#endif