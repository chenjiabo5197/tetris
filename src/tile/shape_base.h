#pragma once

#include "tile.h"

class ShapeBase
{
private:
    // 图形的下降速度累积，用于控制下降的快慢
    float m_down_rate_sum;
protected:
    std::vector<Tile*> m_tile_vector;
    
public:
    ShapeBase(/* args */);
    ~ShapeBase();
    
    // 获取当前图形的tile信息
    std::vector<Tile*> get_tiles_info();

    // 同一图像变换形状
    void shape_change();

    // 图形下落
    bool shape_down(const float& down_rate);

    // 图形向左移动
    bool shape_left();

    // 图形向右移动
    bool shape_right();
};



