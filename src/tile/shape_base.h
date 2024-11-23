#pragma once

#include "tile.h"

class ShapeBase
{
private:
    // 图形的下降速度累积，用于控制下降的快慢
    float m_down_rate_sum;
protected:
    // 代表当前图形的tile集合
    std::vector<Tile*> m_tile_vector;

    // 代表当前图形下一种形态的tile集合
    std::vector<Tile*> m_next_tile_vector;

    // 代表当前shape形状，初始化为0
    short m_current_shape;
    
public:
    ShapeBase(/* args */);
    ~ShapeBase();

    ShapeBase(const ShapeBase& shape);
    
    // 获取当前图形的tile信息
    std::vector<Tile*> getTilesInfo() const;

    // 获取当前图形变化形状后的tile信息
    virtual std::vector<Tile*> getNextTilesInfo();

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

    // 更新m_current_shape
    virtual void updateCurrentShape();

    virtual void resetShape(const tile_sprites& type, const int& defaultTileX = -1, const int& defaultTileY = -1);
};



