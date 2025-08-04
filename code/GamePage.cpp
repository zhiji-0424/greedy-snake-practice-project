#include "GamePage.hpp"

GamePage::GamePage()
{
    page_name = "GamePage";
}

GamePage::~GamePage()
{

}

void GamePage::init()
{

}

void GamePage::handle(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_QUIT) {
        GetAppState()->page_manager->request_exit();
    } else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_AC_BACK) {
        GetAppState()->page_manager->request_exit();
    }
}

void GamePage::update()
{

}

void GamePage::draw()
{
    SDL_SetRenderDrawColorFloat(GetAppState()->renderer, 0.0f, 0.0f, 1.0f, 1.0f);
    SDL_RenderClear(GetAppState()->renderer);

    GetAppState()->page_manager->request_draw();
}