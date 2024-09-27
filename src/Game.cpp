#include "Game.h"
#include <iostream>
#include <SDL2/include/SDL.h>
#include <SDL2/include/SDL_image.h>
#include <glm/glm.hpp>
#include <spdlog/sinks/stdout_color_sinks-inl.h>
#include <spdlog/spdlog.h>


Game::Game() {
	isRunning = false;
	spdlog::info("Game destructor working");
}


Game::~Game() {
	spdlog::info ("Game destructor working");
}

void Game::Initialize() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		spdlog::error("Error Initialize SDL");
		return;
	}

	window = SDL_CreateWindow("My Game Engine",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,windowWidht,windowHeight,0);
	if (!window) {
		spdlog::error( "Error Creating SDL Window" );
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowHeight = displayMode.h;
	windowWidht= displayMode.w;

	renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) {
		spdlog::error("Error creating SDL renderer");
	}

	isRunning = true;
}

void Game::Run() {
	Setup();
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
			}
			break;
		}
	}
}

glm::vec2 playerPosition;
glm::vec2 playerVelocity;

void Game::Setup() {
	playerPosition = glm::vec2(10.0, 20.0);
	playerVelocity = glm::vec2(100.0, 5.0);
}

void Game::Update() {
	//if FPS is down then wait FPS
	//int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	//if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
		//SDL_Delay(timeToWait);
	//}

	//delta time 
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
	//Store the current frame time
	millisecsPreviousFrame = SDL_GetTicks();

	playerPosition.x += playerVelocity.x*deltaTime;
	playerPosition.y += playerVelocity.y*deltaTime;
				
}

void Game::Render() {
	// Arka planı beyaz yapın (R: 255, G: 255, B: 255, A: 255)
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	//Drawing PNG

	SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect dstRect = {
		static_cast<int>(playerPosition.x),static_cast<int>(playerPosition.y),32,32
	};

	SDL_RenderCopy(renderer, texture, NULL, &dstRect);
	SDL_DestroyTexture(texture);
	// Render işlemini güncelleyin // Double Buffer
	SDL_RenderPresent(renderer);
}

void Game :: Destroy() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}