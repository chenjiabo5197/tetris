#pragma once

#include "shape_base.h"
#include "global.h"

class ShapeI: public ShapeBase
{
private:
    /* data */
public:
    ShapeI(const tile_sprites& type);
    ~ShapeI();
};

