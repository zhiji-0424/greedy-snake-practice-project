#ifndef GAMEPAGE_HPP_INCLUDED
#define GAMEPAGE_HPP_INCLUDED

#include "Page.hpp"
#include "PageManager.hpp"
#include "AppState.hpp"
#include "TileMap.hpp"

class GamePage : public Page
{
    public:
    GamePage();
    ~GamePage();
    void init();
    void handle(const SDL_Event& event);
    void update();
    void draw();
    private:
    TileMap tile_map;
};

#endif // GAMEPAGE_HPP_INCLUDED