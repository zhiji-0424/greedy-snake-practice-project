#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>
#include "Food.hpp"
// #include "Common.hpp"

enum class SnakeDirection
{
    up, down, left, right, // 四个方向
    zero
};
std::string to_string(SnakeDirection direction)
{
    switch (direction)
    {
    case SnakeDirection::up:
        return "up";
    case SnakeDirection::down:
        return "down";
    case SnakeDirection::left:
        return "left";
    case SnakeDirection::right:
        return "right";
    case SnakeDirection::zero:
        return "zero";
    default:
        return "unknown";
    }
}

typedef struct snake_node_st
{
    int x, y;
    struct snake_node_st* next;
    // 使用两个方向来表示拐角方向
    SnakeDirection direction, last_direction;
    snake_node_st() {
        x = y = 0;
        direction = SnakeDirection::zero;
        last_direction = SnakeDirection::zero;
        next = nullptr;
    }
} SnakeNode;

class Snake {
    public:
        Snake();
        ~Snake();

        void reset(); // 初始化这条蛇
        void kill();

        void forward(int nw, int nh);               // 画布的横竖格数
        void delete_tail();                         // 删除一节尾巴
        void change_direction(SnakeDirection direction);      // 提交更改蛇头方向(可能不接受更改)
        void set_head_position(int x, int y);       // 设置蛇头位置
        void set_head_direction(SnakeDirection direction);    // 设置蛇头方向

        bool is_eat_food(int x, int y) const;
        bool is_eat_self() const;
        bool is_food_in_snake(int x, int y) const;
        bool is_in_wall(int nw, int nh) const;

        void draw(const vec4& canvas, int nw, int nh);  // 画布的位置、大小（像素）
        // void set_color_head(int color_r, int color_g, int color_b);
        // void set_color_body(int color_r, int color_g, int color_b);

        int get_length() const {return length;};

        double get_degree(SnakeDirection direction, SnakeDirection last_direction) const; // 获取方向对应的角度
        double get_degree(SnakeDirection direction) const;
    private:
        int length;
        SnakeNode head;
        SimpleImage head_img;
        SimpleImage body_img;
        SimpleImage body_corner_img;
        SimpleImage tail_img;
};



#endif
