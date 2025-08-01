cmake_minimum_required(VERSION 3.5)

project(eating-snake)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 代码文件
set(SNAKE_SOURCE_FILES
    code/main.cpp
)

add_executable(eating-snake ${SNAKE_SOURCE_FILES})

# 链接库
target_link_libraries(eating-snake
    SDL3::SDL3
    dear_imgui
    stb
)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

# MSVC 字符编码
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# ================================================================================

# SDL3
# 强制 SDL3 构建静态库
set(SDL_STATIC ON CACHE BOOL "Build static libraries" FORCE)
set(SDL_SHARED OFF CACHE BOOL "Build shared libraries" FORCE)
add_subdirectory(SDL3-3.2.16 EXCLUDE_FROM_ALL)

# dear imgui
set(DEAR_IMGUI_DIR DearImGui-1.92.1/)
set(DEAR_IMGUI_SRC
    ${DEAR_IMGUI_DIR}/imgui_draw.cpp
    ${DEAR_IMGUI_DIR}/imgui_tables.cpp
    ${DEAR_IMGUI_DIR}/imgui_widgets.cpp
    ${DEAR_IMGUI_DIR}/imgui.cpp
    ${DEAR_IMGUI_DIR}/backends/imgui_impl_sdl3.cpp
    ${DEAR_IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
add_library(dear_imgui STATIC ${DEAR_IMGUI_SRC})
target_include_directories(dear_imgui PUBLIC ${DEAR_IMGUI_DIR} ${DEAR_IMGUI_DIR}/backends)
target_link_libraries(dear_imgui PUBLIC SDL3::SDL3)

# stb
set(STB_DIR stb-date-05.26/)
set(STB_SRC
    code/stb_image.cpp
)
add_library(stb STATIC ${STB_SRC})
target_include_directories(stb PUBLIC ${STB_DIR})

# ================================================================================
