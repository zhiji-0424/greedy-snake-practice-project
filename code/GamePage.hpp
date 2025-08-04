#ifndef GAMEPAGE_HPP_INCLUDED
#define GAMEPAGE_HPP_INCLUDED

#include "Page.hpp"
#include "PageManager.hpp"
#include "AppState.hpp"

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
};

#endif // GAMEPAGE_HPP_INCLUDED