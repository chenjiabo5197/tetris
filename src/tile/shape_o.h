#pragma once

#include "shape_base.h"
#include "global.h"

class ShapeO: public ShapeBase
{
private:
    /* data */
public:
    ShapeO(const tile_sprites& type);
    ~ShapeO();

    // 获取当前图形变化形状后的tile信息
    std::vector<Tile*> getNextTilesInfo();

    // 更新m_current_shape
    void updateCurrentShape();
};

