#ifndef __GAME_H__
#define __GAME_H__

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <random>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Vector.h"

// windows
#ifdef __WIN32
#define Main SDL_main
#endif

// other
#ifndef __WIN32
#define Main main
#endif

#define FRAMERATE 60 

class m_Player
{
public:
	m_Player(SDL_Renderer * renderer) {
		p_Surface = NULL;
        p_Texture = NULL;
        p_Renderer = renderer;
	}
	~m_Player() {
		SDL_DestroyTexture(p_Texture);
	}
    void init();
	void render(Sint32 x, Sint32 y); 
    SDL_Rect getPos();
    int getWidth();
    int getHeight();

private:
	SDL_Surface * p_Surface;
	SDL_Texture * p_Texture;
 	SDL_Renderer * p_Renderer;
    SDL_Rect p_position;
	int p_w;
	int p_h;
};

class m_Enemy
{
public:
    m_Enemy(SDL_Renderer * renderer) {
        e_Surface = NULL;
        e_Texture = NULL;
        e_renderer = renderer;
        target = NULL;
        velo = new vec2(0,0);
        acceleration = new vec2(0,0);
        maxforce = 0.1;
        maxspeed = 4;
        srand(time(0));
        wangle = rand()%361;
        wdistance = 4;
        wforce = 10;
        wchange = 50;
    }
    ~m_Enemy() {
        SDL_DestroyTexture(e_Texture);
    }
    void init();
    void render(SDL_Renderer *renderer,int width,int height);
    SDL_Rect getPos();
    int getWidth();
    int getHeight();
    void Move(m_Player* target);
    void Wander();

    m_Player* target;
    vec2 *velo;
    vec2 *acceleration;
    
private:
    SDL_Surface *e_Surface;
    SDL_Texture *e_Texture;
    int e_w;
    int e_h;
    SDL_Renderer* e_renderer;
    std::default_random_engine e_randomW; 
    std::default_random_engine e_randomH;
    std::default_random_engine r_randomW; 
    std::default_random_engine r_randomH;
    std::vector<SDL_Rect> e_position;
    float maxforce;
    float maxspeed;
    float wangle;
    float wdistance;
    float wforce;
    float wchange;
};

class m_Game
{
public:
    m_Game() {
        m_window = NULL;
        m_renderer = NULL;
        width = 1280;
        height = 720;
        m_font = NULL;
        m_colour = {0,0,0,255};
        sightrange = 600;
    }
    ~m_Game() {
        SDL_DestroyWindow(m_window);
        SDL_DestroyRenderer(m_renderer);
        TTF_Quit();
        SDL_Quit();
    }
    void init();
    void loop();
    void render();
    void renderTTF(char *text);

private:
    SDL_Window *m_window;
	SDL_Renderer *m_renderer;

	SDL_Surface *m_backgroundSurface;
	SDL_Texture *m_backgroundTexture;
	
	m_Enemy * m_enemy; 
	m_Player * m_player; 

    float sightrange;
	
	int width; 
	int height;
	
	Sint32 m_playerX;
	Sint32 m_playerY;
	
    // Font
	TTF_Font * m_font; 
	SDL_Surface * m_fontSurface;
	SDL_Texture * m_fontTexture;
	SDL_Colour m_colour; 
};

#endif