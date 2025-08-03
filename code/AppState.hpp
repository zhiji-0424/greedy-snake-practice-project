#ifndef APPSTATE_HPP_INCLUDED
#define APPSTATE_HPP_INCLUDED

#include <SDL3/SDL.h>
// #include "SDL_ttf.h"
#include <string>

class PageManager;

// 仅作为结构使用
class AppState
{
public:
    // 数据保存位置
    std::string data_path;
    
    // 资源存储位置
    std::string res_path;

    // 系统名称
    std::string system_name;

    // 窗口
    SDL_Window* window;

    // 渲染器
    SDL_Renderer* renderer;

    // 字体
    // TTF_Font* font;

    // 页面管理器
    PageManager* page_manager;

    static AppState* instance;

    AppState() : data_path("./data/"), res_path("./res/"), system_name("Unknown"), window(nullptr), renderer(nullptr), page_manager(nullptr)
    {
        instance = this;
    }

    ~AppState()
    {
        instance = nullptr;
    }
};

AppState* GetAppState();


#endif // APPSTATE_HPP_INCLUDED
