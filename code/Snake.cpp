#include "Snake.hpp"

#define LOGE(...) SDL_LogError(SDL_LOG_CATEGORY_ERROR, __VA_ARGS__)
#define LOGD(...) SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, __VA_ARGS__)

static SnakeNode* alloc_node()
{
    SnakeNode* node = new SnakeNode();
    if (node == nullptr) {
        LOGE("alloc_node(): new SnakeNode 出错!");
        return nullptr;
    }
    return node;
}

void Snake::reset()
{
    kill();

    length = 1;
    head.x = 3;
    head.y = 3;
    head.direction = SnakeDirection::zero;
    head.last_direction = head.direction;
    head.next = nullptr;
}

void Snake::kill()
{
    while (length > 1) {
        delete_tail();
    }
}

Snake::Snake()
{
    reset();

    head_img.load_image(        GetAppState()->res_path + "snake_appearance/head.png");
    body_img.load_image(        GetAppState()->res_path + "snake_appearance/body.png");
    body_corner_img.load_image( GetAppState()->res_path + "snake_appearance/body_corner.png");
    tail_img.load_image(        GetAppState()->res_path + "snake_appearance/tail.png");
}

Snake::~Snake()
{
    kill();
}

// todo 方向成功更改后，禁止再次更改
void Snake::change_direction(SnakeDirection d)
{
    head.last_direction = head.direction; // 记录上一次的方向
    if ( (head.direction==SnakeDirection::up) || (head.direction==SnakeDirection::down) ) {
        if ( (d==SnakeDirection::left) || (d==SnakeDirection::right) ) {
            head.direction = d;
        }
    } else if ( (head.direction==SnakeDirection::left) || (head.direction==SnakeDirection::right) ) {
        if ( (d==SnakeDirection::up) || (d==SnakeDirection::down) ) {
            head.direction = d;
        }
    } else {
        LOGE("Snake::change_direction(): 方向错误！值为:(%s)", to_string(head.direction).c_str());
    }
}

// 更新蛇头位置
static void update_head(SnakeNode& head, int nw, int nh)
{
    (void)nw;
    (void)nh;

    if (head.direction == SnakeDirection::up) {
        head.y++; // 向上移动
    } else if (head.direction == SnakeDirection::down) {
        head.y--; // 向下移动
    } else if (head.direction == SnakeDirection::left) {
        head.x--; // 向左移动
    } else if (head.direction == SnakeDirection::right) {
        head.x++; // 向右移动
    } else {
        LOGE("update_head(): head.direction=(%s) 方向错误！", to_string(head.direction).c_str());
    }

    // 穿墙
    /*if (head.x < 0) {
        head.x = nw-1;
    } else if (head.x > nw-1) {
        head.x = 0;
    } else if (head.y < 0) {
        head.y = nh-1;
    } else if (head.y > nh-1) {
        head.y = 0;
    }*/
}

void Snake::forward(int nw, int nh)
{
    // 在头节点后加入节点
    SnakeNode* node = alloc_node();
    node->next = head.next;
    head.next = node;
    this->length += 1;

    // 设置新节点的位置
    node->x = head.x;
    node->y = head.y;
    // 根据头节点的方向设置新节点的方向
    // 只有两截时，新节点方向与头节点相同
    node->direction = head.direction;
    node->last_direction = head.last_direction;

    update_head(head, nw, nh);
    head.last_direction = head.direction;
}

void Snake::delete_tail()
{
    if (length > 1) {
        SnakeNode* t1 = &head; // 作为尾部节点
        SnakeNode* t2 = t1; // 作为尾部节点的前一个节点
        while (t1->next != NULL) {
            t2 = t1;
            t1 = t1->next;
        }
        t2->last_direction = t2->direction; // 更新尾部节点的前一个节点的方向
        free(t1);
        t2->next = NULL;
        length--;
    }
}

void Snake::set_head_position(int x, int y)
{
    head.x = x;
    head.y = y;
}

void Snake::set_head_direction(SnakeDirection d)
{
    head.direction = d;
}

bool Snake::is_eat_food(int x, int y) const
{
    if ( (head.x==x) && (head.y==y) )
        return true;
    return false;
}

bool Snake::is_eat_self() const
{
    SnakeNode* node = head.next;
    while (node) {
        if (node->x == head.x && node->y == head.y)
            return true;
        node = node->next;
    }
    return false;
}

bool Snake::is_food_in_snake(int x, int y) const
{
    const SnakeNode* node = &head;
    while (node) {
        if (node->x == x && node->y == y)
            return true;
        node = node->next;
    }
    return false;
}

bool Snake::is_in_wall(int nw, int nh) const
{
    // 是否穿墙（卡在墙壁）
    if (head.x < 0 || head.x > nw-1 || head.y < 0 || head.y > nh-1) {
        return true;
    }
    return false;
}

// double Snake::get_degree(SnakeDirection direction) const {
//     // 上下左右：0, 180, 270, 90
//     if (direction == SnakeDirection::up) {
//         return 0;
//     } else if (direction == SnakeDirection::down) {
//         return 180;
//     } else if (direction == SnakeDirection::left) {
//         return 270;
//     } else if (direction == SnakeDirection::right) {
//         return 90;
//     }
//     return 0; // 默认返回0
// }

// int Snake::get_degree(SnakeDirection direction, SnakeDirection last_direction) const {
    // 拐角方向
    // if ((last_direction == direction_up && direction == direction_right)
    //     || (last_direction == direction_left && direction == direction_down)) {
    //     return 0;
    // } else if ((last_direction == direction_right && direction == direction_down)
    //     || (last_direction == direction_up && direction == direction_left)) {
    //     return 90;
    // } else if ((last_direction == direction_right && direction == direction_up)
    //     || (last_direction == direction_down && direction == direction_left)) {
    //     return 180;
    // } else if ((last_direction == direction_down && direction == direction_right)
    //     || (last_direction == direction_left && direction == direction_up)) {
    //     return 270;
    // }
    // return 0; // 默认返回0
// }

// void Snake::draw(const vec4& canvas, int nw, int nh)
// {
//     // nw+2 : 边框占位；wall_x+1右移1；nh-1-wall_y+1=(nh-1)-(wall_y-1) -1:下移
//     int block_size = canvas.z / (float)nw;          // 单个格子大小（像素），根据画布大小和格子数量计算
//     const SnakeNode* node = &head;
//     int i = 0; // 标记蛇部位，0为头，1为身体，length-1为尾巴
//     while (node) {
//         // 跳过蛇头
//         if (i!=0) {
//             vec2 p(
//                 canvas.x + node->x*block_size,
//                 canvas.y + (nh-1-node->y)*block_size
//             );
//             if (!(node->last_direction == node->direction)) {
//                 // 绘制拐角
//                 body_corner_img.draw((int)p.x, (int)p.y, block_size, block_size, get_degree(node->direction, node->last_direction));
//             } else {
//                 if (i!=length-1) {
//                     // 绘制身体
//                     body_img.draw((int)p.x, (int)p.y, block_size, block_size, get_degree(node->direction));
//                 } else {
//                     // 绘制蛇尾
//                     tail_img.draw((int)p.x, (int)p.y, block_size, block_size, get_degree(node->direction));
//                 }
//             }
//         }
//         i += 1;
//         node = node->next;
//     }
//     // 绘制蛇头(为了蛇死亡时区分蛇头和身体)
//     vec2 p(
//         canvas.x + head.x*block_size,
//         canvas.y + (nh-1-head.y)*block_size
//     );
//     head_img.draw((int)p.x, (int)p.y, block_size, block_size, get_degree(head.direction));
// }
