#ifndef __VECTOR_H__
#define __VECTOR_H__

// windows
#ifdef __WIN32
#define Main SDL_main
#endif

// other
#ifndef __WIN32
#define Main main
#endif


#include <iostream>

class vec2 
{
public:
    float x;
    float y;

    vec2(float x_, float y_) {
        x = x_;
        y = y_;
    }

    void add(vec2 v) {
        y = y + v.y;
        x = x + v.x;
    }

    void sub(vec2 v) {
        x = x - v.x;
        y = y - v.y;
    }

    void divide(float n) {
        x = x / n;
        y = y / n;
    }

    void multiply(float n) {
        x = x * n;
        y = y * n;
    }

    float magnitude() {
        return sqrt(x*x + y*y);
    }

    void normalize() {
        float n = magnitude();
        if (n != 0) {divide(n);}
    }

    void scare(float s) {
        float m = magnitude();
        if (m > s) {
            x = x * (s/m);
            y = y * (s/m);
        }
    }

    void nega() {
        x = -x;
        y = -y;
    }
};

#endif