#pragma once

#include "tile.h"

class ShapeBase
{
private:

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
    bool shape_down();
};



