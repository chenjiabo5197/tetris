#pragma once

#include "global.h"
#include "config.h"
#include "global.h"

class TileBoard
{
private:
    // 中心点坐标
    int m_center_x;
    int m_center_y;

    // 宽度和长度
    int m_width;
    int m_height;

public:
    TileBoard(const Config& config, const int& width, const int& height);
    ~TileBoard();

    // 渲染函数
    void render();

    // 获取tile_board左上角坐标，用于给tile的坐标设置偏移量
    std::pair<int, int> get_left_top_coordinate();
};



