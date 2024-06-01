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
    std::vector<Tile*> getTilesInfo() const;

    // 同一图像变换形状
    void shapeChange();

    // 图形下落
    bool shapeDown(const float& down_rate);

    // 图形向左移动
    bool shapeLeft();

    // 图形向右移动
    bool shapeRight();

    // 图像渲染
    void render();
};



