#ifndef GAMEPAGE_HPP_INCLUDED
#define GAMEPAGE_HPP_INCLUDED

#include "Page.hpp"
#include "PageManager.hpp"
#include "AppState.hpp"
#include "TileMap.hpp"
#include "Snake.hpp"
#include "Food.hpp"
#include "Wall.hpp"

class GamePage : public Page
{
    public:
    GamePage();
    ~GamePage();
    void init();
    void handle(const SDL_Event& event);
    void update();
    void draw();

    // 游戏初始化
    void game_init();
    // 游戏重置
    void game_reset();
    // 游戏销毁清除
    void game_destroy();
    // 处理输入
    void game_action();
    // 逻辑更新
    void game_update();
    // 绘制
    void game_draw();
private:
    TileMap tile_map;
    Snake snake;
    Food food;
    Wall wall;
    int nw=5, nh=3;
    Uint64 snake_time = 0;
};

#endif // GAMEPAGE_HPP_INCLUDED