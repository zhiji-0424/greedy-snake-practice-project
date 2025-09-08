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

    void update();                                      // 更新瓦片大小
    void draw(ImTextureID texture, int x, int y);       // 绘制单个瓦片（坐标为Map的格子），坐标系左上角的图块为原点(0,0)，场景的贴图应平移后再显示

    void SetPosition(int x, int y);                     // 设置Map位置
    void SetSize(int w, int h);                         // 设置Map大小
    void SetTileNum(int n_tile_x, int n_tile_y);        // 设置瓦片数量(横多少，竖多少)
    void SetExternalPadding(int padding_x, int padding_y);        // 设置Map外边距

    private:
    int x, y;               // 左上角坐标
    int w, h;               // Map宽高限制
    int n_tile_x, n_tile_y; // 瓦片数量
    int tile_size;          // 瓦片大小（正方形）
    int padding_x, padding_y; // Map内边距（Map的限制矩形与瓦片阵列的横竖距离）
};

#endif // TILEMAP_HPP_INCLUDED  