# eating-snake

## 介绍

贪吃蛇, 游戏

因为某些原因重开了仓库，原地址是：[贪吃蛇](https://gitee.com/zhiji-0424/eating-snake.git)，有较详细的历史记录。

## 第三方库

- [SDL3](https://www.libsdl.org)


## 许可证

`eating-snake` 由 @zhiji_0424 编写, 许可证是[Mit许可证](https://mit-license.org/)。
**请按照许可证要求使用此仓库。**


## 玩法

1. 点击按钮或屏幕开始游戏
2. 按下方向键控制蛇的移动方向
3. 蛇吃到食物后长度增加
4. 蛇撞到墙壁或自己身体时游戏结束


## 构建

1. 直接解压项目根目录下的3个压缩包。

3. ```shell
    cmake . -Bbuild --DCMAKE_BUILD_TYPE=Release
    cmake --build build
    ```
4. 运行 `build/bin/eating-snake` 即可开始游戏。如果被缩放了，请尝试`右键程序-属性-兼容性-更改高DPI设置-替代高DPI缩放行为`

## 待办事项
6. 死亡时震动（Android）
8. 分数记录（附加时间）
9. 规则说明：移动、死亡、开始暂停
13. 显示更新内容

### 尝试（暂不执行）
1. 用户名与昵称
4. 头像
5. 联机排行榜
