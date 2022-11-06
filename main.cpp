#include "Game.h"


// To compile:
// g++ -std=c++14 -o play -I ./include/ -I/Library/Frameworks/SDL2.framework/Headers ./*.cpp -F/Library/Frameworks -framework SDL2 -I/Library/Frameworks/SDL2_image.framework/Headers -F/Library/Frameworks -framework SDL2_image -lSDL2_ttf

int main(int argc, char **argv) {
    m_Game game;
    game.init();
    game.loop();
    return 0;
}