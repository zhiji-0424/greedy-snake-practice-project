#include "Wall.hpp"

Wall::Wall()
{
    stage_in_bg.load_image(GetAppState()->res_path + "ui/stage_in.png");
    stage_out_bg.load_image(GetAppState()->res_path + "ui/stage_out.png");
}

Wall::~Wall()
{
}

// void Wall::draw(const vec4& canvas, int nw, int nh)
// {
//     (void)nh;
//     // nw+2 : 边框占位；wall_x+1右移1；nh-1-wall_y+1=(nh-1)-(wall_y-1) -1:下移
//     int block_size = canvas.z/(float)(nw+2);          // 单个格子大小（像素）
//     stage_out_bg.draw(canvas.x,
//                       canvas.y,
//                       canvas.z,
//                       canvas.w);
//     stage_in_bg.draw(canvas.x+block_size,
//                      canvas.y+block_size,
//                      canvas.z-2*block_size,
//                      canvas.w-2*block_size);
// }
