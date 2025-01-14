#pragma once
#define GAME_H
#include <SDL2/include/SDL.h>
#include <SDL2/include/SDL_image.h>

const int FPS = 120 ;
const int MILLISECS_PER_FRAME = 1000 / FPS;
class Game {
private:
	bool isRunning;
	int millisecsPreviousFrame=0;
	SDL_Window* window;
	SDL_Renderer* renderer;
public:
	Game();
	~Game();
	void Initialize();
	void Run();
	void Setup();
	void ProcessInput();
	void Update();
	void Render();
	void Destroy();

	int windowWidht= 800;
	int windowHeight=600;
};
