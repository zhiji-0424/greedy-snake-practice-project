#include "TileMap.hpp"
#include "imgui.h"

void TileMap::init()
{

}

void TileMap::update()
{
    // 根据宽高和瓦片数量设置瓦片大小，要比较两者宽高比例
    float ratio_mapsize = (float)w / (float)h;
    float ratio_tile = (float)n_tile_x / (float)n_tile_y;
    if (ratio_mapsize > ratio_tile) {
        tile_size = h / n_tile_y;
    } else {
        tile_size = w / n_tile_x;
    }
}

void TileMap::draw(ImTextureID texture, int x, int y)
{
    // 坐标系左上角的图块为原点(0,0)
    int tile_x = x * tile_size;
    int tile_y = y * tile_size;
    ImGui::GetForegroundDrawList()->AddImage(texture, ImVec2(tile_x, tile_y), ImVec2(tile_x + tile_size, tile_y + tile_size));
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
