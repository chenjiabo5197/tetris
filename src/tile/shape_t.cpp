#include "shape_t.h"

// tile_board的第一层中间，用于新tile出现的定位
extern int g_tile_board_middle;
// tile边长
extern int g_tile_length;

ShapeT::ShapeT(const tile_sprites& type)
{
    for (size_t i = 0; i < 3; i++)
    {
        Tile* temp = new Tile(type);
        temp->set_coordinate((g_tile_board_middle-1+i)*g_tile_length, g_tile_length);
        m_tile_vector.push_back(temp);
    }
    Tile* temp = new Tile(type);
    temp->set_coordinate((g_tile_board_middle)*g_tile_length, 0);
    m_tile_vector.push_back(temp);
    INFOLOG("ShapeT construct success");
}

ShapeT::~ShapeT()
{ 
    INFOLOG("ShapeT ~ShapeT success");
}