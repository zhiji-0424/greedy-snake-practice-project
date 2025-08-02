#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <stb_image.h>
#include <string>

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    if (!SDL_CreateWindowAndRenderer("examples/renderer/clear", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
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
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
    // Fonts
    // io.Fonts->AddFontFromFileTTF("/storage/emulated/0/Documents/Misans-Normal.ttf");
    io.Fonts->AddFontDefault();


    return SDL_APP_CONTINUE;
}

std::string eventToString(const SDL_Event& event) {
    switch (event.type) {
        case SDL_EVENT_QUIT:
            return "SDL_EVENT_QUIT";

        case SDL_EVENT_KEY_DOWN:
            // SDL3 新版：直接使用 event.key.key 表示键位码
            return "SDL_EVENT_KEY_DOWN [key=" + std::to_string(event.key.key) + "]";

        case SDL_EVENT_KEY_UP:
            return "SDL_EVENT_KEY_UP [key=" + std::to_string(event.key.key) + "]";

        case SDL_EVENT_MOUSE_MOTION:
            return "SDL_EVENT_MOUSE_MOTION [x=" + std::to_string(event.motion.x) + 
                   ", y=" + std::to_string(event.motion.y) + "]";

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            return "SDL_EVENT_MOUSE_BUTTON_DOWN [button=" + std::to_string(event.button.button) + "]";

        case SDL_EVENT_MOUSE_BUTTON_UP:
            return "SDL_EVENT_MOUSE_BUTTON_UP [button=" + std::to_string(event.button.button) + "]";

        /*case SDL_EVENT_WINDOW_EVENT:
            switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                    return "SDL_WINDOWEVENT_RESIZED [w=" + std::to_string(event.window.data1) + 
                           ", h=" + std::to_string(event.window.data2) + "]";
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    return "SDL_WINDOWEVENT_FOCUS_GAINED";
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    return "SDL_WINDOWEVENT_FOCUS_LOST";
                default:
                    return "SDL_WINDOWEVENT [type=" + std::to_string(event.window.event) + "]";
            }*/

        case SDL_EVENT_TEXT_INPUT:
            return "SDL_EVENT_TEXT_INPUT [text=" + std::string(event.text.text) + "]";

        default:
            return "SDL_EVENT [type=" + std::to_string(event.type) + "]";
    }
}

void printEvent(const SDL_Event& event) {
    SDL_Log("%s", eventToString(event).c_str());
}

#include <stdlib.h>
char editing_text[100000];

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;
    } else if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_AC_BACK) {
        return SDL_APP_SUCCESS;
    }
    if (event->type == SDL_EVENT_FINGER_DOWN) {
        //if (!SDL_TextInputActive(window))
            //SDL_StartTextInput(window);
    }
    if (event->type == SDL_EVENT_TEXT_EDITING) {
        sprintf(editing_text, "%s", event->edit.text);
    }
    if (event->type == SDL_EVENT_TEXT_INPUT) {
        sprintf(editing_text, "%s", event->text.text);
    }
    // printEvent(*event);
    ImGui_ImplSDL3_ProcessEvent(event);
    return SDL_APP_CONTINUE;
}

Uint64 frame_time = 0;
int target_fps = 60;
bool image_loaded = false;
int w, h, n;
SDL_Texture *texture = 0;
float scale = 1.0f;
char buf[100000];
bool need_draw = true;

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    
    
    
    
    if (need_draw) {
        // 计算帧率
        Uint64 frame_start = SDL_GetTicks();
    
        ImGuiIO& io = ImGui::GetIO();
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */
        /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
        const float red = (float) (0.5 + 0.5 * SDL_sin(now));
        const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
        const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
        SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */
        SDL_RenderClear(renderer);
    
        // if (ImGui::Button("close keyboard")) {
            
        // }
        ImGui::Begin("hhh");
        ImGui::Text("frame rate: %.1f", io.Framerate);
        ImGui::Text("SDL_TextInputActive(window): %s", SDL_TextInputActive(window)?"yes":"no");
        ImGui::Text("目标帧率: %d", target_fps);
        ImGui::Text("frame time: %lu", frame_time );
        ImGui::SliderInt("target fps", &target_fps, 30, 360);
        ImGui::SliderFloat("缩放蒽蒽蒽蒽蒽蒽蒽蒽图片", &scale, 0, 5);
        // ImGui::InputTextMultiline("str", buf, 100000, ImVec2(800,0));
        // ImGui::Text("%s", editing_text);
        ImGui::End();

        if (!image_loaded) {
            unsigned char *data = stbi_load("/storage/emulated/0/Download/20250625135715.png", &w, &h, &n, 0);
            if (data) {
                SDL_Surface *surface = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGB24, data, n*w);
                if (surface) {
                    texture = SDL_CreateTextureFromSurface(renderer, surface);
                    SDL_DestroySurface(surface);
                } else {
                    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "surface 创建错误：%s", SDL_GetError());
                }
                stbi_image_free(data);
            } else {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "stb加载错误：%s", stbi_failure_reason());
            }
            image_loaded = true;
        }
        ImGui::Text("宽：%d，高：%d，通道：%d", w, h, n);
        ImGui::Image((ImTextureID)(intptr_t)texture, ImVec2(w*scale, h*scale));

        // Rendering
        ImGui::Render();
        SDL_SetRenderScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    
        // 计算帧率
        frame_time = SDL_GetTicks() - frame_start;
        if (1000.0f/target_fps > frame_time*1.0) {
            SDL_Delay(1000.0f/target_fps - frame_time*1.0);
        }
    }
    
    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    // Cleanup
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

