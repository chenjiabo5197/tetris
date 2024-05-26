#pragma once

#include "SDL2/SDL.h"
#include "global.h"
#include "common.h"
#include "sdl_texture.h"

class Tile
{
private:
    //tile 的渲染位置
    SDL_Rect m_box;

    //tile 的渲染类型
    tile_sprites m_type;

    // tile坐标偏移量
    int m_offset_x;
    int m_offset_y;

public:
    //Initializes position and type
    Tile(const tile_sprites& type);

    //Get the tile type
    tile_sprites getType();

    //获取碰撞盒
    SDL_Rect getBox();

    void render();

    // 设置tile坐标
    bool set_coordinate(const int& x, const int& y);
};