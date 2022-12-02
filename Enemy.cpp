#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void m_Enemy::init() {
    bool success = true;
    std::stringstream errorStream;

    e_Surface = IMG_LoadPNG_RW(SDL_RWFromFile("enemy.png","rb")); 
    if (e_Surface == NULL) {
        errorStream << "Cannot open enemy.png! Error: " << SDL_GetError() << "\n";
		success = false;
    }
		
	e_w = e_Surface->w;
	e_h = e_Surface->h;
		
	e_Texture = SDL_CreateTextureFromSurface(e_renderer, e_Surface);
	SDL_FreeSurface(e_Surface);
	e_Surface = NULL;

    if (e_Texture == NULL) {
        errorStream << "Cannot create enemy texture! " << "\n";
		success = false;
	}

    if (!success)
    {
		errorStream << "m_Enemy::Enemy - Failed to initialize!\n";
		std::string errors = errorStream.str();
		SDL_Log("%s\n", errors.c_str());
	}
}

void m_Enemy::render(SDL_Renderer * renderer, int width, int height) {
	static std::uniform_int_distribution<int> e_uniformW(0,width);	
    static std::uniform_int_distribution<int> e_uniformH(0,height);

    // initialize
    if (e_position.empty()) {
	    e_randomW.seed((unsigned)time(NULL) + e_randomW()); 		
	    int w = e_uniformW(e_randomW);
        e_randomH.seed((unsigned)time(NULL) + e_randomH()); 
        int h = e_uniformH(e_randomH);
	    SDL_Rect srcrect = {w,h,e_w,e_h};
	    e_position.push_back(srcrect);
        e_position.push_back(srcrect);
    }	

    //edge
    if (e_position[0].x > 1280) {
		e_position[0].x = 0;
	}

	if (e_position[0].x < 0) {
		e_position[0].x = 1280;
	}

	if (e_position[0].y > 720) {
		
		e_position[0].y = 0;
	}

	if (e_position[0].y < 0) {
		
		e_position[0].y = 720;
	}

    // move
    if (target == NULL) {
        Wander();
    }
    else {
        Move(target);
    }
       
	SDL_RenderCopy(renderer, e_Texture, NULL, &e_position[0]);	
}

void m_Enemy::Move(m_Player* target) {

    vec2 desire = vec2(0,0);
    desire.x = target->getPos().x - e_position[0].x; 
    desire.y = target->getPos().y - e_position[0].y;
    desire.normalize();
    desire.multiply(maxspeed);
    desire.sub(*velo);

    vec2 steer = desire;
    steer.scare(maxforce);
    
    acceleration->add(steer);
    velo->add(*acceleration);
    velo->scare(maxspeed);
    e_position[0].x += velo->x;
    e_position[0].y += velo->y;
    acceleration->multiply(0);

    return;
}

float random_range(float wchange) {
    srand(time(0));
    float r = rand()%(int)(2*wchange);
    return r-wchange;
}

// wandering
void m_Enemy::Wander() {
    vec2 desire = *velo;
    desire.scare(wdistance);
    vec2 v = vec2(wforce*cos(atan2(velo->y, velo->x)+wangle), wforce*sin(atan2(velo->y,velo->x)+wangle));
    desire.add(v);
    desire.scare(maxforce);
    wangle += random_range(wchange);
    vec2 steer = desire;
    acceleration->add(steer);
    velo->add(*acceleration);
    velo->scare(maxspeed);
    e_position[0].x += velo->x;
    e_position[0].y += velo->y;
    acceleration->multiply(0); 
}
	
SDL_Rect m_Enemy::getPos() {
    return e_position[0]; // we only have 1 enemy now
}

int m_Enemy::getWidth() {
    return e_w;
}

int m_Enemy::getHeight() {
    return e_h;
}
	
