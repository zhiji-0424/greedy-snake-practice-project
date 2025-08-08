#include "PageManager.hpp"
#include "Page.hpp"

// #ifndef NODEARIMGUI // 引入imgui
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
// #endif


PageManager::PageManager()
{
    current_page = 0;
    new_page = 0;
    exit_requested = false;
    need_to_draw = false;

    imgui_create_context();
}

PageManager::~PageManager()
{
    imgui_destroy_context();
    // if (bgm) {
    //     Mix_FreeMusic(bgm);
    // }
}

void PageManager::first_page(Page* first_page)
{
    if (first_page) {
        if (new_page) {
            delete new_page;
        }
        new_page = first_page;
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s:first_page(): %s", "PageManager", first_page->page_name.c_str());
    } else {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s:first_page(): NULL", "PageManager");
    }
    // 播放背景音乐
    // bgm = Mix_LoadMUS((GetAppState()->res_path + "audio/Roa - Bloom.mp3").c_str());
    // if (!bgm) {
    //      zj_logger_e("GamePage", "音频加载失败: Roa - Bloom.mp3");
    // } else {
    //     Mix_VolumeMusic(MIX_MAX_VOLUME * 0.1f);
    //     Mix_PlayMusic(bgm, -1);
    // }
}

void PageManager::request_exit()
{
    exit_requested = true;
    if (current_page)
        delete current_page;
    current_page = nullptr;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "PageManager:%s", "request_exit()");
}

void PageManager::request_page(Page* new_page_)
{
    if (new_page) {
        delete new_page;
    }
    new_page = new_page_;
    std::string page_name;
    if (current_page) {
        page_name = current_page->page_name;
        delete current_page;
        current_page = nullptr;
    }
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s: request_page() %s --> %s", "PageManager", page_name.c_str(), new_page_->page_name.c_str());
}

void PageManager::request_draw()
{
    need_to_draw = true;
}

void PageManager::do_event(SDL_Event* event)
{
    imgui_process_input(*event); // imgui处理输入
    if (current_page)
        current_page->handle(*event); // 处理事件
}


void PageManager::do_step()
{
    // 换页
    if (new_page) {
        if (current_page)
            delete current_page;
        current_page = new_page;
        new_page = nullptr;
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s: 新页面: %s", "PageManager", current_page->page_name.c_str());
        current_page->init(); // 初始化
    }

    if (current_page)
        current_page->update(); // 更新

    // 请求退出
    if (exit_requested) {
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s: 退出请求已接受", "PageManager");
        // 后续交给主程序
    }
}

void PageManager::do_draw()
{
    if (!current_page) {
        need_to_draw = false;
        return;
    }

    imgui_new_frame();
    current_page->draw();
    imgui_end_frame();

    if (need_to_draw) {
        imgui_render_data();

        // 显示
        SDL_RenderPresent(GetAppState()->renderer);

        need_to_draw = false;
    }
}

void PageManager::imgui_create_context() {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.IniFilename = "/sdcard/Documents/imgui.ini";
    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    float main_scale = SDL_GetDisplayContentScale(SDL_GetPrimaryDisplay());
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (using io.ConfigDpiScaleFonts=true makes this unnecessary. We leave both here for documentation purpose)
    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(GetAppState()->window, GetAppState()->renderer);
    ImGui_ImplSDLRenderer3_Init(GetAppState()->renderer);
    // Fonts
    if (SDL_GetPlatform() == std::string("Android")) {
        io.Fonts->AddFontFromFileTTF("/storage/emulated/0/Documents/Misans-Normal.ttf");
    } else {
        io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/msyh.ttc");
    }
    io.Fonts->AddFontDefault();
}

void PageManager::imgui_destroy_context() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
}

void PageManager::imgui_process_input(const SDL_Event& event) {
    ImGui_ImplSDL3_ProcessEvent(&event);
}

void PageManager::imgui_new_frame() {
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
}

void PageManager::imgui_end_frame() {
    ImGui::Render();
}

void PageManager::imgui_render_data() {
    ImGuiIO& io = ImGui::GetIO();
    SDL_SetRenderScale(GetAppState()->renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), GetAppState()->renderer);
}