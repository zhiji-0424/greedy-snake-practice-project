#include "HelloPage.hpp"
#include <SDL3/SDL.h>
#include <imgui.h>
#include "GamePage.hpp"

HelloPage::HelloPage()
{
    page_name = "HelloPage";
}

HelloPage::~HelloPage()
{
    
}

void HelloPage::init()
{

}

void HelloPage::handle(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_QUIT) {
        GetAppState()->page_manager->request_exit();
    } else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_AC_BACK) {
        GetAppState()->page_manager->request_exit();
    }
}

float scale = 4.1f;

void HelloPage::update()
{
    if (scale > 4.0f) {
        GetAppState()->page_manager->request_page(new GamePage());
    }
}

extern int target_fps;


void HelloPage::draw()
{
    ImGuiIO& io = ImGui::GetIO();

    SDL_SetRenderDrawColorFloat(GetAppState()->renderer, 1, 1, 1, 1);
    SDL_RenderClear(GetAppState()->renderer);

    ImGui::Begin("hhh");
    ImGui::Text("frame rate: %.1f", io.Framerate);
    ImGui::Text("SDL_TextInputActive(window): %s", SDL_TextInputActive(GetAppState()->window)?"yes":"no");
    ImGui::SliderFloat("缩放图片", &scale, 0, 5);
    ImGui::SliderInt("target fps", &target_fps, 30, 360);
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    ImGui::Text("main scale: %.2f", main_scale);
    ImGui::End();

    GetAppState()->page_manager->request_draw();
}