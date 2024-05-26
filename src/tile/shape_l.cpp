#include "shape_l.h"

// tile_board的第一层中间，用于新tile出现的定位
extern int tile_board_middle;
// tile边长
extern int tile_length;

ShapeL::ShapeL(const tile_sprites& type)
{
    for (size_t i = 0; i < 4; i++)
    {
        Tile* temp = new Tile(type);
        temp->set_coordinate((tile_board_middle-2+i)*tile_length, 0);
        m_tile_vector.push_back(temp);
    }
}

ShapeL::~ShapeL()
{ 
}