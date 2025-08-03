#ifndef PAGE_HPP
#define PAGE_HPP

#include <SDL3/SDL.h>
#include "AppState.hpp"
#include <string>

class Page {
    friend class PageManager;

    public:
        Page();
        virtual ~Page();
        // 由 PageManager 调用
        virtual void init()=0;
        virtual void handle(const SDL_Event& event)=0;
        virtual void update()=0;
        virtual void draw()=0; // 需要 request_draw()
    protected:
        // bool has_focus;
        std::string page_name;
};

#endif
