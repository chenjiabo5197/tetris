#include "shape_l.h"

// tile_board的第一层中间，用于新tile出现的定位
extern int g_tile_board_middle;
// tile边长
extern int g_tile_length;

ShapeL::ShapeL(const tile_sprites& type)
{
    for (size_t i = 0; i < 3; i++)
    {
        Tile* temp = new Tile(type);
        temp->setRelativeCoordinate((g_tile_board_middle-1+i)*g_tile_length, g_tile_length);
        m_tile_vector.push_back(temp);
    }
    Tile* temp = new Tile(type);
    temp->setRelativeCoordinate((g_tile_board_middle-1)*g_tile_length, 0);
    m_tile_vector.push_back(temp);
    INFOLOG("ShapeL construct success");
}

ShapeL::~ShapeL()
{ 
    INFOLOG("ShapeL ~ShapeL success");
}

std::vector<Tile*> ShapeL::getNextTilesInfo()
{
    // 先清空m_next_tile_vector
    m_next_tile_vector.clear();
    // I只有两种形态
    switch (m_current_shape)
    {
    case 0:
    {
        // 横向转化为竖向
        // 第三块tile不变，为基准
        auto base_tile = m_tile_vector.at(2);
        tile_sprites base_type = base_tile->getType();
        int base_tile_x = base_tile->getBox().x;
        int base_tile_y = base_tile->getBox().y;
        auto first_tile = new Tile(base_type);
        first_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y-2*g_tile_length);
        m_next_tile_vector.push_back(first_tile);
        auto second_tile = new Tile(base_type);
        second_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y-g_tile_length);
        m_next_tile_vector.push_back(second_tile);
        m_next_tile_vector.push_back(base_tile);
        auto forth_tile = new Tile(base_type);
        forth_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(forth_tile);
        break;
    }
    case 1:
    {
        // 竖向转化为横向
        // 第三块tile不变，为基准
        auto base_tile = m_tile_vector.at(2);
        tile_sprites base_type = base_tile->getType();
        int base_tile_x = base_tile->getBox().x;
        int base_tile_y = base_tile->getBox().y;
        auto first_tile = new Tile(base_type);
        first_tile->setAbsoluteCoordinate(base_tile_x-2*g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(first_tile);
        auto second_tile = new Tile(base_type);
        second_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(second_tile);
        m_next_tile_vector.push_back(base_tile);
        auto forth_tile = new Tile(base_type);
        forth_tile->setAbsoluteCoordinate(base_tile_x+g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(forth_tile);
        break;
    }
    default:
        ERRORLOG("getNextTilesInfo||unknown m_current_shape||m_current_shape={}", m_current_shape);
        break;
    }
    return m_next_tile_vector;
}

void ShapeL::updateCurrentShape()
{
    // I只有两种形态
    switch (m_current_shape)
    {
    case 0:
        // 横向转化为竖向
        m_current_shape = 1;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    case 1:
        // 竖向转化为横向
        m_current_shape = 0;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    default:
        ERRORLOG("updateCurrentShape||unknown m_current_shape||m_current_shape={}", m_current_shape);
        break;
    }
}