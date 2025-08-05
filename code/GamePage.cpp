#include "GamePage.hpp"
#include "Snake.hpp"

Snake snake;

GamePage::GamePage()
{
    page_name = "GamePage";
}

GamePage::~GamePage()
{

}

void GamePage::init()
{
    snake.init();
    snake.set_head_direction(SnakeDirection::up);
    snake.forward(10, 10);
    snake.forward(10, 10);
    snake.forward(10, 10);
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

    snake.forward(10, 10);
    snake.delete_tail();    
}

void GamePage::draw()
{
    SDL_SetRenderDrawColorFloat(GetAppState()->renderer, 0.0f, 0.0f, 1.0f, 1.0f);
    SDL_RenderClear(GetAppState()->renderer);

    for (int i=0; i<200; i++) {
        // Snake
        int x, y;
        // SnakeDirection d;
        snake.get_position(x, y, i);
        // snake.get_direction(d, i);
        tile_map.draw(snake.get_head_texture_id(), x, y);
    }

    GetAppState()->page_manager->request_draw();
}