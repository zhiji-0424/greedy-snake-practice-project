#include "Food.hpp"

Food::Food()
{
    x = 0;
    y = 0;
}

void Food::create(int nw, int nh)
{
    // 需要重置种子，保证每次随机数不同
    x = rand() % (nw==0? 1 : nw);
    y = rand() % (nh==0? 1 : nh);

    if (!image_loaded) {
        food_image.load_image(GetAppState()->res_path + "snake_appearance/food.png");
        image_loaded = true;
    }
}

Food::~Food()
{
    x = 0;
    y = 0;
}

// void Food::draw(const vec4& canvas, int nw, int nh)
// {
//     // canvas 舞台大小位置信息

//     // 格子大小
//     int block_size = canvas.z / (float)nw;
//     vec2 p(
//         canvas.x + position.x*block_size,
//         canvas.y + (nh-1-position.y)*block_size
//     );
//     // food_image.draw((int)p.x, (int)p.y, block_size, block_size);
// }