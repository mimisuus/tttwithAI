#include <SDL.h>
#include <string>
#include <array>

#include "minimax.h"
#include "logic.h"

const int SCREENW = 800;
const int SCREENH = 640;
const int SQUAREW = SCREENW / 3;
const int SQUAREH = SCREENH / 3;
const std::string STARTING_PLAYER = "human";

auto drawTurn = [](int pos, bool player1, SDL_Renderer* renderer) {
	int padding = 50;
	int x = (pos % 3) * SQUAREW;
	int y = (pos / 3) * SQUAREH;

	if (player1) {
		SDL_Rect rectangle;
		rectangle.x = x + padding; rectangle.y = y + padding;
		rectangle.w = SQUAREW - (padding * 2); rectangle.h = SQUAREH - (padding * 2);
		SDL_RenderDrawRect(renderer, &rectangle);
	}
	else {
		SDL_RenderDrawLine(renderer, x + padding, y + padding, x + SQUAREW - padding, y + SQUAREH - padding);
		SDL_RenderDrawLine(renderer, x + SQUAREW - padding, y + padding, x + padding, y + SQUAREH - padding);
	}
};

int main(int argc, char* args[]) {

	// AI
	minimax minimax;

	// SDL
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
	if (SDL_CreateWindowAndRenderer(SCREENW, SCREENH, 0, &window, &renderer) == 0) {
		bool done = false;

		/*
		012
		345
		678
		*/
		std::array<int, 9> board = { 0 };

		// checkerboard pattern
		SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
		SDL_RenderDrawLine(renderer, SQUAREW, 0, SQUAREW, SCREENH);
		SDL_RenderDrawLine(renderer, SQUAREW * 2, 0, SQUAREW * 2, SCREENH);
		SDL_RenderDrawLine(renderer, 0, SQUAREH, SCREENW, SQUAREH);
		SDL_RenderDrawLine(renderer, 0, SQUAREH * 2, SCREENW, SQUAREH * 2);
		SDL_RenderPresent(renderer);

		if (STARTING_PLAYER != "human") {
			int aiTurn = minimax.getMove(board);
			if (aiTurn != -1) drawTurn(aiTurn, false, renderer);
			SDL_RenderPresent(renderer);
		}

		while(!done){			
			SDL_Event event;

			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_QUIT) {
					done = true;
				}
				else if (event.type == SDL_MOUSEBUTTONUP) {
					int x, y;
					SDL_GetMouseState(&x, &y);
					int posx = x / SQUAREW; // 0, 1, 2
					int posy = y / SQUAREH * 3; // 4, 5, 6
					int pos = posx + posy;
					if (board[pos] == 0) {
						board[pos] = 1;
						drawTurn(pos, true, renderer);
						int aiTurn = minimax.getMove(board);
						if (aiTurn != -1) drawTurn(aiTurn, false, renderer);
						SDL_RenderPresent(renderer);
					}

					// End screen
					int gameState = checkWin(board);
					if (gameState != 0) {
						std::string endScreen = (gameState < 3) ? "P" + std::to_string(gameState) + " won" : "Tie";
						SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
							"Game Over",
							endScreen.c_str(),
							NULL);
						done = true;
					}
				}
				
			}
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}