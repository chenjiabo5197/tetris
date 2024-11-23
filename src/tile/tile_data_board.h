/*============================================
* Author: chenjiabo
* E-mail: chen_wangyi666@163.com
* Date: 2024-1-14
* Description: This is chess_data_board.h file
* Copyright (c) 2023, All rights reserved
=============================================*/
#pragma once

#include <SDL2/SDL.h>
#include <map>
#include <iomanip>
#include "sdl_timer.h"
#include "sdl_ttf.h"
#include "common.h"
#include "global.h"
#include "my_utils.h"
#include "logger.h"
#include "config.h"
#include "sdl_window.h"
#include "shape_base.h"

class TileDataBoard
{
private:
	// 数据中心渲染的字体
    SDLTTF* m_data_board_ttf;

    // 数据板中心坐标
    int m_data_board_x;
    int m_data_board_y;

    // 总计时器，显示当前对局进行的时间
    SDLTimer* m_top_timer;

    // 显示当前获取的分数
    int m_gameScore;

    ShapeBase* m_next_shape_base;
    tile_sprites m_tile_type;

    // 渲染文字到指定位置
	void renderText(const std::string& texture_text, TTF_Font* texture_ttf, SDL_Color color, const int& x, const int& y, const float& multiple);

public:
    TileDataBoard(const Config& config);
    ~TileDataBoard();

    // 初始化，传入渲染所需参数
	void init();

	// 初始化数据板信息
	void initDataBoard();

    // 重置数据板信息
    void resetDataBoard();

    // 数据版渲染
    void render();

    // 更新比分信息
    void updateScoreInfo();

    // 开始单人游戏，设置一些数据
    void startSingleGame();

    // 游戏暂停/结束
    void pauseTimer();

    // 游戏分数增加
    void scoreAdd();

    // 设置下一个图像
    void setNextShape(ShapeBase* shape, const tile_sprites& tile_type);

};



