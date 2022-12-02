#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

void m_Game::init() {
    bool success = true;
    std::stringstream errorStream;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		errorStream << "SDL could not initialize! SDL Error: " << SDL_GetError() << "\n";
		success = false;
	}
    else 
    {
        m_window = SDL_CreateWindow("myGame", 
                                    SDL_WINDOWPOS_UNDEFINED,
									SDL_WINDOWPOS_UNDEFINED,
									width,
									height,
									SDL_WINDOW_SHOWN);
        if (m_window == NULL)
		{
			errorStream << "Window could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
		}

        m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
        if (m_renderer == NULL)
        {
            errorStream << "Renderer could not be created! SDL Error: " << SDL_GetError() << "\n";
			success = false;
        }

        IMG_Init(IMG_INIT_PNG);
        TTF_Init();
		m_font = TTF_OpenFont("OpenSans-Bold.ttf",16);
    }

    if (!success)
	{
		errorStream << "m_Game::game - Failed to initialize!\n";
		std::string errors = errorStream.str();
		SDL_Log("%s\n", errors.c_str());
	}
	
}

void m_Game::loop() {
    bool quit = false;
    SDL_Event e;
    m_enemy = new m_Enemy(m_renderer);
    m_enemy->init();
    m_player = new m_Player(m_renderer);
    m_player->init();

    uint32_t Begin,End,_time,rate;
	int32_t delay;

    while(!quit) {
        Begin = SDL_GetTicks();
		render();
        while (SDL_PollEvent(&e) != 0)
		{
            if (e.type == SDL_QUIT)
			{
				quit = true;
			}

            if (e.type == SDL_MOUSEMOTION) {
                if (e.motion.x >=0 && e.motion.x + m_player->getWidth() <= width){
                    if (e.motion.y >=0 && e.motion.y + m_player->getHeight() <= height){
                        m_playerX = e.motion.x;
					    m_playerY = e.motion.y; 
                    }
                }		
			}

		}
        End = SDL_GetTicks();
		_time = End - Begin;
		rate = 1000 / FRAMERATE;
		delay = rate - _time;
			
		if (delay > 0) {
			SDL_Delay(delay);
		}
    }  
   
}

float distance(m_Enemy *e, m_Player *p) {
    float result = sqrt((e->getPos().x - p->getPos().x) * (e->getPos().x - p->getPos().x)
                   +(e->getPos().y - p->getPos().y) * (e->getPos().y - p->getPos().y));
    return result;
}

void m_Game::render() {
    SDL_SetRenderDrawColor(m_renderer,200,200,200,200);
	SDL_RenderClear(m_renderer);

    static int health = 100;

    m_player->render(m_playerX,m_playerY);
    m_enemy->render(m_renderer,width,height);
    if (distance(m_enemy, m_player) <= sightrange) {
        m_enemy->target = m_player; 
    }
    else {
        m_enemy->target = NULL;
    }
    
    char text[14];
    
    if (abs(m_player->getPos().x - m_enemy->getPos().x) < (m_enemy->getWidth() + m_player->getWidth())/2 
        && abs(m_player->getPos().y - m_enemy->getPos().y) < (m_enemy->getHeight() + m_player->getHeight())/2)
    {
        if (health > 0) {health--;}
        else {health = 0;}   
    }
    sprintf(text,"Health: %d",health);
    renderTTF(text);
   
    SDL_RenderPresent(m_renderer);
}

void m_Game::renderTTF(char * text) {

    bool success = true;
    std::stringstream errorStream;

    m_fontSurface = TTF_RenderText_Solid(m_font, text, m_colour);
    if (m_fontSurface == NULL) {
        errorStream << "Cannot create font surface " << SDL_GetError() << "\n";
		success = false;
    }

	int w,h;
	w = m_fontSurface->w;
	h = m_fontSurface->h;
		
	m_fontTexture = SDL_CreateTextureFromSurface(m_renderer,m_fontSurface);
	if (m_fontTexture == NULL) {
		errorStream << "Cannot create font texture! " << "\n";
		success = false;
	}
	SDL_FreeSurface(m_fontSurface);
	m_fontSurface = NULL;
		
	SDL_Rect srcrect = {0,0,w*4,h*4};
	SDL_RenderCopy(m_renderer, m_fontTexture, NULL, &srcrect);
    SDL_DestroyTexture(m_fontTexture);
    if (!success)
    {
		errorStream << "Font - Failed to initialize!\n";
		std::string errors = errorStream.str();
		SDL_Log("%s\n", errors.c_str());
	}
}