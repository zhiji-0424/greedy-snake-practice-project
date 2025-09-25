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
    snake.init();
    snake.set_head_direction(SnakeDirection::up);
    snake.forward(nw, nh);
    snake.forward(nw, nh);
    snake.can_through_wall = true;

    do {
        food.create(nw, nh);
    } while (snake.is_food_in_snake(food.x, food.y));
}

void GamePage::handle(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_QUIT) {
        GetAppState()->page_manager->request_exit();
    } else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_AC_BACK) {
        GetAppState()->page_manager->request_exit();
    }

    if (event.type == SDL_EVENT_KEY_DOWN) {
        switch (event.key.key) {
            case SDLK_UP:
            snake.change_direction(SnakeDirection::up);
            break;
            case SDLK_DOWN:
            snake.change_direction(SnakeDirection::down);
            break;
            case SDLK_LEFT:
            snake.change_direction(SnakeDirection::left);
            break;
            case SDLK_RIGHT:
            snake.change_direction(SnakeDirection::right);
            break;
        }
    }
}

void GamePage::update()
{
    int w, h;
    SDL_GetCurrentRenderOutputSize(GetAppState()->renderer, &w, &h);
    tile_map.SetSize(w, h);
    tile_map.SetTileNum(nw+2, nh+2);
    tile_map.SetPosition(0, 0);
    tile_map.SetExternalPadding(10, 15);
    tile_map.update();

    if (SDL_GetTicks() - snake_time > 200) {
        snake_time = SDL_GetTicks();
        snake.forward(nw, nh);
        // SDL_Delay(200);

        if (snake.is_eat_food(food.x, food.y)) {
            do {
                food.create(nw, nh);
            } while (snake.is_food_in_snake(food.x, food.y));
        } else {
            snake.delete_tail();
        }
    }
}

void GamePage::draw()
{
    SDL_SetRenderDrawColorFloat(GetAppState()->renderer, 0.0f, 0.0f, 0.0f, 1.0f);
    SDL_RenderClear(GetAppState()->renderer);

    for (int i=0; i<nw+2; i++) {
        for (int j=0; j<nh+2; j++) {
            if (i>0 && i<nw+1 && j>0 && j<nh+1) {
                tile_map.draw(wall.GetTextureID(0), i, j);
            } else {
                tile_map.draw(wall.GetTextureID(1), i, j);
            }
        }   
    }

    tile_map.draw(food.GetTextureID(), food.x+1, food.y+1);

    for (int i=snake.get_length()-1; i>=0; i--) {
        int x, y;
        snake.get_position(x, y, i);
        x++;
        y++;
        tile_map.draw(snake.get_texture_id(i), x, y);
    }

    // 需要TileMap的方块部分的坐标，todo：导出接口
    // ImGui::GetForegroundDrawList()->AddText(ImVec2(100, 100), IM_COL32_BLACK, "hello你好", 0);

    GetAppState()->page_manager->request_draw();
}

// 游戏初始化
void GamePage::game_init()
{

}

// 游戏重置
void GamePage::game_reset()
{
    
}

// 游戏销毁清除
void GamePage::game_destroy()
{
    
}

// 处理输入
void GamePage::game_action()
{
    
}

// 逻辑更新
void GamePage::game_update()
{
    
}

// 绘制
void GamePage::game_draw()
{
    
}