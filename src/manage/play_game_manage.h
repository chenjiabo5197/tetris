/*============================================
* Author: chenjiabo
* E-mail: chen_wangyi666@163.com
* Date: 2024-1-3
* Description: 下棋页面管理，负责下棋页面的渲染
* Copyright (c) 2023, All rights reserved
=============================================*/
#pragma once

#include <vector>
#include <SDL2/SDL.h>
#include "set"
#include "common.h"
#include "global.h"
#include "my_utils.h"
#include "sdl_button.h"
#include "sdl_window.h"
#include "logger.h"
#include "config.h"
#include "tile_board.h"
#include "tile.h"
#include "shape_base.h"
#include "shape_i.h"
#include "shape_j.h"
#include "shape_l.h"
#include "shape_o.h"
#include "shape_s.h"
#include "shape_t.h"
#include "shape_z.h"
#include "tile_data_board.h"

class PlayGameManage
{
private:  
    // 当前页面要渲染的按键数组
    SDLButton* m_playchess_buttons[1];

    TileBoard* m_tile_board;

    // 数据板
    TileDataBoard* m_data_board;

    // 按键的数组长度，渲染按键时使用
    int m_array_length;

    //当前页面所有按键的中心位置，按键以此为中心，纵向分布
    int m_buttons_x;
    int m_buttons_y;

    // 按键之间的间隔(上下间隔)
    int m_button_interval;

    // tile源图路径
    std::string m_tiles_path;

    // tile_board 尺寸
    int m_tile_board_row_nums;
    int m_tile_board_col_nums;

    // 存放当前要渲染的所有tile
    std::vector<Tile*> m_tile_vector;

    // 上次随机图形的索引
    short m_last_shape_index;
    // 上次随机颜色的索引
    short m_last_tile_sprite_index;

    // 判断当前图形是否可以下降、左移、右移
    bool isCanDown(const ShapeBase& shape);
    bool isCanLeft(const ShapeBase& shape);
    bool isCanRight(const ShapeBase& shape);

    // 判断游戏是否结束
    bool isGameOver(const ShapeBase& shape);

    // 图像是否可以变换形状，若图形变换位置会造成tile重叠或超出tile_board范围，则不能变换形状
    bool isShapeCanChange(ShapeBase& shape);

    // 获取下一个出现的图形
    ShapeBase* nextShape(const tile_sprites& type);

    // 下一个出现的图形颜色
    tile_sprites nextTileSprite();

    // 判断tile当前行是否可消除，若可消除则消除，不可消除跳过
    bool updateEliminate(const int& row);

    // 获取当前shape可以下降的最大距离
    int distanceCanShapeDown(const ShapeBase& shape);

public:
    PlayGameManage(const Config& config);
    ~PlayGameManage();

    void startRender();

    // 初始化
    void init();

    // 处理事件
    void handleEvents(SDL_Event* event);

    // 处理鼠标点击事件
    bool handleMouseClick(SDL_Event* event);

};



