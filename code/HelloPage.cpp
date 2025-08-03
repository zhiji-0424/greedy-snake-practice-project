#include "HelloPage.hpp"
#include "SDL3/SDL.h"

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

#include <stdlib.h>
char editing_text[100000];

void HelloPage::handle(const SDL_Event& event)
{
    if (event.type == SDL_EVENT_QUIT) {
        GetAppState()->page_manager->request_exit();
    } else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_AC_BACK) {
        GetAppState()->page_manager->request_exit();
    }
    if (event.type == SDL_EVENT_FINGER_DOWN) {
        //if (!SDL_TextInputActive(window))
            //SDL_StartTextInput(window);
    }
    if (event.type == SDL_EVENT_TEXT_EDITING) {
        sprintf(editing_text, "%s", event.edit.text);
    }
    if (event.type == SDL_EVENT_TEXT_INPUT) {
        sprintf(editing_text, "%s", event.text.text);
    }
}
void HelloPage::update()
{
    
}
void HelloPage::draw()
{
    GetAppState()->page_manager->request_draw();
}