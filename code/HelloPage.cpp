#include "HelloPage.hpp"
#include <SDL3/SDL.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <stb_image.h>
#include "SimpleImage.hpp"
#include "Food.hpp"

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

float scale = 1.0f;

void HelloPage::update()
{
    
}

extern int target_fps;


void HelloPage::draw()
{
    ImGuiIO& io = ImGui::GetIO();

    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(GetAppState()->renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
    SDL_RenderClear(GetAppState()->renderer);

    // if (ImGui::Button("close keyboard")) {
        
    // }
    ImGui::Begin("hhh");
    ImGui::Text("frame rate: %.1f", io.Framerate);
    ImGui::Text("SDL_TextInputActive(window): %s", SDL_TextInputActive(GetAppState()->window)?"yes":"no");
    ImGui::SliderFloat("缩放图片", &scale, 0, 5);
    // ImGui::InputTextMultiline("str", buf, 100000, ImVec2(800,0));
    // ImGui::Text("%s", editing_text);
    ImGui::End();

    ImGui::SliderInt("target fps", &target_fps, 30, 360);
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    ImGui::Text("main scale: %.2f", main_scale);
    GetAppState()->page_manager->request_draw();
}