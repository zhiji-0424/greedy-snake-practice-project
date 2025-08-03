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
    if (new_page) {
        delete new_page;
    }
    new_page = first_page;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s:first_page(): %s", "PageManager", first_page->page_name.c_str());

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
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "PageManager:%s", "request_exit()");
}

void PageManager::request_page(Page* new_page_)
{
    if (new_page) {
        delete new_page;
    }
    new_page = new_page_;
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "request_page() %s --> %s", "PageManager", current_page->page_name.c_str(), new_page_->page_name.c_str());
}

void PageManager::request_draw()
{
    need_to_draw = true;
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

    imgui_new_frame();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        imgui_process_input(event); // imgui处理输入
        if (current_page)
            current_page->handle(event); // 处理事件
    }
    if (current_page)
        current_page->update(); // 更新

    // 请求退出
    if (exit_requested) {
        if (current_page)
            delete current_page;
        current_page = nullptr;
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s: 退出请求已接受", "PageManager");
        // 后续交给主程序
    }
}

void PageManager::do_draw()
{
    if (!current_page)
        return;

    // 渲染到目标
    // imgui_new_frame();
    current_page->draw();
    imgui_end_frame();

    if (need_to_draw) {
        // 渲染到屏幕
        imgui_render_data();

        // 显示
        SDL_RenderPresent(GetAppState()->renderer);

        need_to_draw = false;
    }
}

void PageManager::imgui_create_context() {
// #ifndef NODEARIMGUI
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(GetAppState()->window, GetAppState()->renderer);
    ImGui_ImplSDLRenderer3_Init(GetAppState()->renderer);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
// #endif
}

void PageManager::imgui_destroy_context() {
// #ifndef NODEARIMGUI
    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
// #endif
}

void PageManager::imgui_process_input(const SDL_Event& event) {
    (void)event;
// #ifndef NODEARIMGUI
    ImGui_ImplSDL3_ProcessEvent(&event);
// #endif
}

void PageManager::imgui_new_frame() {
// #ifndef NODEARIMGUI
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui_ImplSDL3_NewFrame();
    ImGui::NewFrame();
// #endif
}

void PageManager::imgui_end_frame() {
// #ifndef NODEARIMGUI
    // end_frame
    ImGui::Render();
// #endif
}

void PageManager::imgui_render_data() {
// #ifndef NODEARIMGUI
    // Rendering
    ImGuiIO& io = ImGui::GetIO();
    SDL_SetRenderScale(GetAppState()->renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), GetAppState()->renderer);
// #endif
}