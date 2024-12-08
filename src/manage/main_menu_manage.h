/*============================================
* Author: chenjiabo
* E-mail: chen_wangyi666@163.com
* Date: 2024-1-3
* Description: 主菜单管理，负责主菜单的渲染
* Copyright (c) 2024, All rights reserved
=============================================*/
#pragma once

#include <SDL2/SDL.h>
#include "sdl_button.h"
#include "sdl_window.h"
#include "logger.h"
#include "config.h"
#include "global.h"
#include "my_utils.h"
#include "sdl_ttf.h"

class MainMenuManage
{
private:
   
    // 当前页面要渲染的按键数组
    SDLButton* m_main_menu_buttons[3];

    // 数组长度
    int m_array_length;

    // 当前页面所有按键的中心位置，按键以此为中心，纵向分布
    int m_buttons_x;
    int m_buttons_y;

    // 按键之间的间隔(上下间隔)
    int m_button_interval;

    // 判断是否在展示排行榜页面
    bool m_is_show_best_score;

    // 排行榜渲染
    void bestScoreRender();

    // 排行榜界面返回主界面按键
    SDLButton* backMenuButton;

    std::vector<BestScoreUser> bestScoreVector;

    // 排行榜的渲染字体
    SDLTTF* m_data_board_ttf;

    void renderText(const std::string& texture_text, TTF_Font* texture_ttf, SDL_Color color, const int& x, const int& y, const float& multiple);
    
public:
    MainMenuManage(const Config& config);
    ~MainMenuManage();

    void startRender();

    // 初始化
    void init();

    // 处理事件
    void handleEvents(SDL_Event* event);

    // 查看分数排行榜
    void showBestScore();
};
