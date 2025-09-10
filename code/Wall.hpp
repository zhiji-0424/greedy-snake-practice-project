#ifndef WALL_HPP
#define WALL_HPP

#include "Common.hpp"
#include <SDL3/SDL.h>
#include "AppState.hpp"
#include "SimpleImage.hpp"

class Wall {
    public:
        Wall();
        ~Wall();
        // void draw(const vec4& canvas, int nw, int nh);

        // index: 0 内; 1 外
        ImTextureID GetTextureID(int i);
    private:
        SimpleImage stage_out_bg;
        SimpleImage stage_in_bg;
        bool image_loaded = false;
};

#endif
