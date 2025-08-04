#include "GamePage.hpp"
#include "Food.hpp"

Food food;

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
    int w, h;
    SDL_GetCurrentRenderOutputSize(GetAppState()->renderer, &w, &h);
    tile_map.SetSize(w, h);
    tile_map.SetTileNum(20, 10);
    tile_map.SetPosition(0, 0);
    tile_map.SetExternalPadding(10, 10);
    tile_map.update();
}

void GamePage::draw()
{
    SDL_SetRenderDrawColorFloat(GetAppState()->renderer, 0.0f, 0.0f, 1.0f, 1.0f);
    SDL_RenderClear(GetAppState()->renderer);

    for (int i=0; i<200; i++) {
        food.create(20, 10);
        tile_map.draw(food.GetTextureID(), food.x, food.y);
    }

    GetAppState()->page_manager->request_draw();
}