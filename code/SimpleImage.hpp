#ifndef SIMPLEIMAGE_HPP_INCLUDED
#define SIMPLEIMAGE_HPP_INCLUDED

#include <SDL3/SDL.h>
#include "Common.hpp"
#include "AppState.hpp"
#include <string>
#include <stb_image.h>
#include <imgui.h>

#define SimpleImage_DEBUG_TAG "SimpleImage"

// 加载图片并上传纹理
class SimpleImage {
    protected:
        SDL_Texture* m_texture;
        int width, height, channels;    // 图片的宽高和通道数

    public:
        SimpleImage() {
            m_texture = nullptr;
        }

        ~SimpleImage() {
            if (m_texture) {
                SDL_DestroyTexture(m_texture);
                m_texture = nullptr;
            }
        }

        // 切换纹理
        void set_image(SDL_Texture* texture) {
            if (texture) {
                if (m_texture) {
                    SDL_DestroyTexture(m_texture);
                }
                m_texture = texture;
            }
        }

        // 加载纹理
        void load_image(const std::string &path) {
            load_image(path.c_str());
        }
        void load_image(const char* path) {
            // 使用stb_image.h加载png图像
            unsigned char* data = stbi_load(path, &width, &height, &channels, 0);
            if (data) {
                // 从data创建texture
                SDL_PixelFormat format = ((channels==3) ? SDL_PIXELFORMAT_RGB24 : SDL_PIXELFORMAT_RGBA32);
                // !!!不会复制像素数据。像素数据不受自动管理；在释放像素数据之前，必须先释放表面。!!!
                SDL_Surface* surface = SDL_CreateSurfaceFrom(width, height, format, data, width * channels);
                if (surface) {
                    // 转换surface为texture
                    SDL_Texture* texture = SDL_CreateTextureFromSurface(GetAppState()->renderer, surface);
                    SDL_DestroySurface(surface);
                    surface = nullptr;
                    if (texture) {
                        SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR);
                        set_image(texture);
                    } else {
                        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s:无法从surface创建texture: %s, (%s)", SimpleImage_DEBUG_TAG, SDL_GetError(), path);
                    }
                } else {
                    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s:无法从data创建surface: %s, (%s)", SimpleImage_DEBUG_TAG, SDL_GetError(), path);
                }
                // 在释放像素数据之前，必须先释放表面。
                stbi_image_free(data);
                data = nullptr;
            } else {
                SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s:stbi_load失败: %s, (%s)", SimpleImage_DEBUG_TAG, stbi_failure_reason(), path);
            }
        }

        //获取纹理
        SDL_Texture* GetTexture() const
        {
            return m_texture;
        }

        ImTextureID GetTextureID() const
        {
            return (ImTextureID)(intptr_t)m_texture;
        }

        void GetTextureInfo(int& w, int& h, int& channels) const
        {
            w = width;
            h = height;
            channels = this->channels;
        }

        // void draw(int x, int y, int w, int h) {
        //     if (m_texture) {
                
        //     }
        // }

        // // 旋转绘制（绕中心）
        // void draw(int x, int y, int w, int h, double angle) {
        //     if (m_texture) {
        //         SDL_Rect rect{x, y, w, h};
        //         SDL_Point center{w / 2, h / 2};
        //         SDL_RenderCopyEx(GetAppState()->renderer, m_texture, nullptr, &rect, angle, &center, SDL_FLIP_NONE);
        //     }
        // }
};

#endif // SIMPLEIMAGE_HPP_INCLUDED
