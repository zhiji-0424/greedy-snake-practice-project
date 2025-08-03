#ifndef FOOD_HPP
#define FOOD_HPP

#include <SDL3/SDL.h>
#include "SimpleImage.hpp"

class Food {
    public:
        Food();
        ~Food();
        void create(int nw, int nh);    // 画布的横竖格数
        // void draw(const vec4& canvas, int nw, int nh);  // 画布的位置、大小（像素）
        int x, y;   // X，Y坐标
    private:
        SimpleImage food_image;
};


#endif