#include "cleanup.h"
#include "res_path.h"
#include "drawing_functions.h"
#include "SDL_mixer.h"

int main(int argc, char **argv) {
	//Setup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Error initializing SDL\n";
		return 1;
	}
	//Setup window
	SDL_Window *window = SDL_CreateWindow("Hack and Slash", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 352, SDL_WINDOW_SHOWN);
	//SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN
	if (window == nullptr) {
		SDL_Quit();
		cout << "Window error\n";
		return 1;
	}
	//Setup renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		cleanup(window);
		SDL_Quit();
		cout << "Renderer error\n";
		return 1;
	}

	SDL_RenderSetLogicalSize(renderer, 640, 352);
	//Initialize SDL_image
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		SDL_Quit();
		cout << "SDL_image error\n";
		return 1;
	}
	//Initialize text to font
	if (TTF_Init() != 0) {
		SDL_Quit();
		cout << "TTF error\n";
		return 1;
	}
	//Initialize SDL_mixer
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		SDL_Quit();
		cout << "Mixer error\n";
		return 1;
	}
	//Load up texture
	string resPath = getResourcePath();
	SDL_Texture *texture = loadTexture(resPath + "map.png", renderer);
	//Run game for 5000ms
	while (SDL_GetTicks() < 5000) {
		//Clear the screen
		SDL_RenderClear(renderer);
		//Draw to screen
		renderTexture(texture, renderer, 0, 0);
		//Show image we've been rendering
		SDL_RenderPresent(renderer);
	}
	cleanup(renderer);
	cleanup(window);
	cleanup(texture);
	SDL_Quit();

	return 0;
}