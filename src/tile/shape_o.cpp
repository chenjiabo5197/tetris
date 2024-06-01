#include "shape_o.h"

// tile_board的第一层中间，用于新tile出现的定位
extern int g_tile_board_middle;
// tile边长
extern int g_tile_length;

ShapeO::ShapeO(const tile_sprites& type)
{
    for (size_t i = 0; i < 2; i++)
    {
        Tile* temp = new Tile(type);
        temp->set_coordinate((g_tile_board_middle-1+i)*g_tile_length, 0);
        m_tile_vector.push_back(temp);
        Tile* temp2 = new Tile(type);
        temp2->set_coordinate((g_tile_board_middle-1+i)*g_tile_length, g_tile_length);
        m_tile_vector.push_back(temp2);
    }
    INFOLOG("ShapeO construct success");
}

ShapeO::~ShapeO()
{ 
    INFOLOG("ShapeO ~ShapeO success");
}