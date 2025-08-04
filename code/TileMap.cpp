#include "TileMap.hpp"
#include "imgui.h"

void TileMap::update()
{
    // 根据宽高和瓦片数量设置瓦片大小，要比较两者宽高比例
    float ratio_mapsize = (float)w / (float)h;
    float ratio_tile = (float)n_tile_x / (float)n_tile_y;
    if (ratio_mapsize > ratio_tile) {
        tile_size = (h - padding_y * 2) / n_tile_y;
    } else {
        tile_size = (w - padding_x * 2) / n_tile_x;
    }
}

void TileMap::draw(ImTextureID texture, int x, int y)
{
    // 坐标系左上角的图块为原点(0,0)
    int offset_x = (w - padding_x * 2 - n_tile_x * tile_size) / 2;
    int offset_y = (h - padding_y * 2 - n_tile_y * tile_size) / 2;
    int tile_x = x * tile_size + this->x + padding_x + offset_x;
    int tile_y = y * tile_size + this->y + padding_y + offset_y;
    ImGui::GetForegroundDrawList()->AddImage(texture, ImVec2(tile_x, tile_y), ImVec2(tile_x + tile_size, tile_y + tile_size));

    // // 绘制外边框
    // ImGui::GetForegroundDrawList()->AddRect(ImVec2(this->x, this->y), ImVec2(this->x + w, this->y + h), IM_COL32_WHITE);
    // // 绘制内边框
    // ImGui::GetForegroundDrawList()->AddRect(ImVec2(this->x + padding_x, this->y + padding_y), ImVec2(this->x + w - padding_x, this->y + h - padding_y), IM_COL32(0, 255, 0, 255));
}

void TileMap::SetPosition(int x, int y)
{
    this->x = x;
    this->y = y;
}

void TileMap::SetSize(int w, int h)
{
    this->w = w;
    this->h = h;
}

void TileMap::SetTileNum(int n_tile_x, int n_tile_y)
{
    this->n_tile_x = n_tile_x;
    this->n_tile_y = n_tile_y;
}

void TileMap::SetExternalPadding(int padding_x, int padding_y)
{
    this->padding_x = padding_x;
    this->padding_y = padding_y;
}