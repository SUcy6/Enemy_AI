#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

void m_Player::init() {
    bool success = true;
    std::stringstream errorStream;

    p_Surface = IMG_LoadPNG_RW(SDL_RWFromFile("player.png","rb"));
    if (p_Surface == NULL) {
        errorStream << "Cannot open player.png! Error: " << SDL_GetError() << "\n";
		success = false;
    }
		
	p_w = p_Surface->w;
	p_h = p_Surface->h;
		
	p_Texture = SDL_CreateTextureFromSurface(p_Renderer, p_Surface);
	SDL_FreeSurface(p_Surface);
	p_Surface = NULL;

    if (p_Texture == NULL) {
        errorStream << "Cannot create player texture! " << "\n";
		success = false;
	}

    if (!success)
    {
		errorStream << "m_Player::Player - Failed to initialize!\n";
		std::string errors = errorStream.str();
		SDL_Log("%s\n", errors.c_str());
	}
}

void m_Player::render(Sint32 x, Sint32 y) {
    SDL_ShowCursor(false);
	SDL_Rect srcrect = {x, y, p_w, p_h};
    p_position = srcrect;
	SDL_RenderCopy(p_Renderer, p_Texture, NULL, &srcrect);
}

SDL_Rect m_Player::getPos() {
    return p_position;
}

int m_Player::getWidth() {
    return p_w;
}

int m_Player::getHeight() {
    return p_h;
}