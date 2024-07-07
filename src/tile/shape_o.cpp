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
        temp->setRelativeCoordinate((g_tile_board_middle-1+i)*g_tile_length, 0);
        m_tile_vector.push_back(temp);
        Tile* temp2 = new Tile(type);
        temp2->setRelativeCoordinate((g_tile_board_middle-1+i)*g_tile_length, g_tile_length);
        m_tile_vector.push_back(temp2);
    }
    m_current_shape = 0;
    INFOLOG("ShapeO construct success");
}

ShapeO::~ShapeO()
{ 
    INFOLOG("ShapeO ~ShapeO success");
}

std::vector<Tile*> ShapeO::getNextTilesInfo()
{
    // 先清空m_next_tile_vector
    m_next_tile_vector.clear();
    // O型没有变化形态
    m_next_tile_vector.insert(m_next_tile_vector.end(), m_tile_vector.begin(), m_tile_vector.end());
    return m_next_tile_vector;
}

void ShapeO::updateCurrentShape()
{
    // O只有1种形态
    switch (m_current_shape)
    {
    case 0:
        // 横向转化为竖向
        m_current_shape = 0;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    default:
        ERRORLOG("updateCurrentShape||unknown m_current_shape||m_current_shape={}", m_current_shape);
        break;
    }
}