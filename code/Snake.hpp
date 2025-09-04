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

std::string to_string(SnakeDirection direction);

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

        void init();    // 初始化（只能开始时调用一次）
        void reset();   // 初始化这条蛇
        void kill();

        void forward(int nw, int nh);                           // 画布的横竖格数
        void delete_tail();                                     // 删除一节尾巴
        void change_direction(SnakeDirection direction);        // 提交更改蛇头方向(可能不接受更改)
        void set_head_position(int x, int y);                   // 设置蛇头位置
        void set_head_direction(SnakeDirection direction);      // 设置蛇头方向
        void get_position(int& x, int& y, int index) const;                 // 获取蛇各节点位置
        void get_direction(SnakeDirection& direction, int index) const;     // 获取蛇各节点方向
        void get_last_direction(SnakeDirection& direction, int index) const;     // 获取蛇各节点上一个方向

        bool is_eat_food(int x, int y) const;
        bool is_eat_self() const;
        bool is_food_in_snake(int x, int y) const;
        bool is_in_wall(int nw, int nh) const;

        int get_length() const {return length;};
        ImTextureID get_head_texture_id(int index) const;           // index 是 head_img 的下标
        ImTextureID get_body_texture_id(int index) const;           // index 是 body_img 的下标
        ImTextureID get_body_corner_texture_id(int index) const;    // index 是 body_corner_img 的下标
        ImTextureID get_tail_texture_id(int index) const;           // index 是 tail_img 的下标
        ImTextureID get_texture_id(int index) const;  // index 是从头(0)开始的下标

        double get_degree(SnakeDirection direction, SnakeDirection last_direction) const; // 获取方向对应的角度
        double get_degree(SnakeDirection direction) const;

        bool can_through_wall = false;
    private:
        int length;
        SnakeNode head;
        SimpleImage head_img[4];
        SimpleImage body_img[4];
        SimpleImage body_corner_img[8];
        SimpleImage tail_img[4];
};



#endif
