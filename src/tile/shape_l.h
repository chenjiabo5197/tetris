#pragma once

#include "shape_base.h"
#include "global.h"

class ShapeL: public ShapeBase
{
private:
    /* data */
public:
    ShapeL(const tile_sprites& type);
    ~ShapeL();

    // 获取当前图形变化形状后的tile信息
    std::vector<Tile*> getNextTilesInfo();

    // 更新m_current_shape
    void updateCurrentShape();

    void resetShape(const tile_sprites& type, const int& defaultTileX = -1, const int& defaultTileY = -1);
};

