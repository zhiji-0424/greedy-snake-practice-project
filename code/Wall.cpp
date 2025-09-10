#include "Wall.hpp"

Wall::Wall()
{
    image_loaded = false;
}

Wall::~Wall()
{
}

ImTextureID Wall::GetTextureID(int i)
{
    if (!image_loaded) {
        stage_in_bg.load_image(GetAppState()->res_path + "snake_appearance/wall_in.png");
        stage_out_bg.load_image(GetAppState()->res_path + "snake_appearance/wall_out.png");
        image_loaded = true;
    }
    switch (i) {
    case 0:
        return stage_in_bg.GetTextureID();
        break;
    case 1:
        return stage_out_bg.GetTextureID();
        break;
    default:
        return 0;
    }
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
