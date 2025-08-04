#ifndef TILEMAP_HPP_INCLUDED
#define TILEMAP_HPP_INCLUDED

#include "imgui.h"

class TileMap
{
    public:
    TileMap() : x(0), y(0), w(0), h(0), n_tile_x(0), n_tile_y(0), tile_size(0)
    {
    }
    ~TileMap()
    {
    }

    void init();
    void update();
    void draw(ImTextureID texture);
    void clear();

    void SetPosition(int x, int y);
    void SetSize(int w, int h);

    private:
    int x, y;               // 左上角坐标
    int w, h;               // 宽高
    int n_tile_x, n_tile_y; // 瓦片数量
    int tile_size;          // 瓦片大小
};

#endif // TILEMAP_HPP_INCLUDED