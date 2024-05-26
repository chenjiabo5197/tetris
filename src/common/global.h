/*============================================
* Author: chenjiabo
* E-mail: chen_wangyi666@163.com
* Date: 2023-12-30
* Description: 储存全局变量
* Copyright (c) 2023, All rights reserved
=============================================*/
#pragma once

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "sdl_window.h"
#include "common.h"

// 背景音乐  // TODO 背景音
extern Mix_Music* g_background_music;

// 选择按键音效
extern Mix_Chunk* g_select_button_sound;

// 主窗口
extern SDLWindow* g_main_window;

// 普通字体
extern TTF_Font* g_normal_font;

// tile的全局加载
extern SDLTexture* g_tile_texture;

// tile每个区域
extern SDL_Rect g_tile_clips[TOTAL_TILE_SPRITES];

// tile边长
extern int tile_length;

// 每个tile1的偏移量
extern std::pair<int, int> tile_offset;

// tile_board的第一层中间，用于新tile出现的定位
extern int tile_board_middle;