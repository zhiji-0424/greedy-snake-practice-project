#ifndef PAGEMANAGER_HPP
#define PAGEMANAGER_HPP

#include <SDL3/SDL.h>
#include "Page.hpp"

class PageManager {
    public:
        PageManager();
        ~PageManager();

        void first_page(Page* first_page);

        // 请求退出
        void request_exit();
        // 请求新页面
        void request_page(Page* new_page);
        // 请求绘图
        void request_draw();

        // 由主程序调用
        bool ready_to_exit() {return exit_requested;}

        void do_step();     // 在这里换页（调用完 Page->step() 之后）
        void do_draw();
    private:
        // 新页面 临时指针
        Page* new_page;

        // 当前页面指针
        Page* current_page;

        // 是否请求退出
        bool exit_requested;

        // 是否需要绘图
        bool need_to_draw;

        // imgui 相关
        void imgui_create_context();
        void imgui_destroy_context();
        void imgui_process_input(const SDL_Event& event);
        void imgui_new_frame();
        void imgui_end_frame();
        void imgui_render_data();

        // 背景音乐
        // Mix_Music *bgm;
};

#endif
