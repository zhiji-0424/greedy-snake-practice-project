#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "AppState.hpp"
#include "PageManager.hpp"
#include "HelloPage.hpp"
#include <imgui.h>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("贪吃蛇", "1.0", "net.zhiji.snake");

    SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);

    new AppState();
    GetAppState()->system_name = SDL_GetPlatform();
    if (GetAppState()->system_name == "Android") {
        GetAppState()->data_path = SDL_GetPrefPath(nullptr, nullptr) + std::string("/data/");
        GetAppState()->res_path  = ""; // 待测试
        if (!SDL_CreateDirectory(GetAppState()->data_path.c_str())) {
            SDL_Log("Couldn't create directory: %s", SDL_GetError());
        }
    } else {
        GetAppState()->data_path = "./data/";
        GetAppState()->res_path  = "./res/";
        if (!SDL_CreateDirectory(GetAppState()->data_path.c_str())) {
            SDL_Log("Couldn't create directory: %s", SDL_GetError());
        }
        if (!SDL_CreateDirectory(GetAppState()->res_path.c_str())) {
            SDL_Log("Couldn't create directory: %s", SDL_GetError());
        }
    }

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer("贪吃蛇", 640, 480,
                                    SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY,
                                    &GetAppState()->window, &GetAppState()->renderer)) {
        SDL_Log("Couldn't create window orrenderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    GetAppState()->page_manager = new PageManager();
    GetAppState()->page_manager->first_page(new HelloPage());

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    GetAppState()->page_manager->do_event(event);
    if (GetAppState()->page_manager->ready_to_exit()) {
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

Uint64 frame_time = 0;
int target_fps = 60;

SDL_AppResult SDL_AppIterate(void *appstate)
{
    // 计算帧率
    Uint64 frame_start = SDL_GetTicks();

    GetAppState()->page_manager->do_step();
    if (GetAppState()->page_manager->ready_to_exit()) {
        return SDL_APP_SUCCESS;
    }

    ImGui::SliderInt("target fps", &target_fps, 30, 360);

    GetAppState()->page_manager->do_draw();
    if (GetAppState()->page_manager->ready_to_exit()) {
        return SDL_APP_SUCCESS;
    }

    // 计算帧率
    frame_time = SDL_GetTicks() - frame_start;
    if (1000.0f/target_fps > frame_time*1.0) {
        SDL_Delay(1000.0f/target_fps - frame_time*1.0);
    }
    
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    delete GetAppState()->page_manager;
    SDL_DestroyRenderer(GetAppState()->renderer);
    SDL_DestroyWindow(GetAppState()->window);
    delete GetAppState();
    SDL_Quit();
}

