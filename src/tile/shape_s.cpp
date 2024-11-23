#include "shape_s.h"

// tile_board的第一层中间，用于新tile出现的定位
extern int g_tile_board_middle;
// tile边长
extern int g_tile_length;

ShapeS::ShapeS(const tile_sprites& type)
{
    resetShape(type);
    INFOLOG("ShapeS construct success");
}

ShapeS::~ShapeS()
{ 
    INFOLOG("ShapeS ~ShapeS success");
}

void ShapeS::resetShape(const tile_sprites& type, const int& defaultTileX, const int& defaultTileY)
{ 
    ShapeBase::resetShape(type, defaultTileX, defaultTileY);
    for (size_t i = 0; i < 2; i++)
    {
        Tile* temp = new Tile(type);
        if(defaultTileX == -1)
        {
            temp->setRelativeCoordinate((g_tile_board_middle-1+i)*g_tile_length, g_tile_length);
        }
        else
        {
            temp->setAbsoluteCoordinate(defaultTileX+(-1+i)*g_tile_length, defaultTileY + g_tile_length);
        }
        m_tile_vector.push_back(temp);
    }
    for (size_t i = 0; i < 2; i++)
    {
        Tile* temp = new Tile(type);
        if(defaultTileX == -1)
        {
            temp->setRelativeCoordinate((g_tile_board_middle+i)*g_tile_length, 0);
        }
        else
        {
            temp->setAbsoluteCoordinate(defaultTileX+i*g_tile_length, defaultTileY);
        }
        m_tile_vector.push_back(temp);
    }
}

std::vector<Tile*> ShapeS::getNextTilesInfo()
{
    // 先清空m_next_tile_vector
    m_next_tile_vector.clear();
    // 第二块tile不变，为基准
    auto base_tile = m_tile_vector.at(1);
    tile_sprites base_type = base_tile->getType();
    int base_tile_x = base_tile->getBox().x;
    int base_tile_y = base_tile->getBox().y;
    auto first_tile = new Tile(base_type);
    auto third_tile = new Tile(base_type);
    auto forth_tile = new Tile(base_type);
    // I只有两种形态
    switch (m_current_shape)
    {
    case 0:
        // 横向S顺时针旋转90度
        first_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y-g_tile_length);
        m_next_tile_vector.push_back(first_tile);
        m_next_tile_vector.push_back(base_tile);
        third_tile = m_tile_vector.at(0);
        m_next_tile_vector.push_back(third_tile); 
        forth_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    case 1:
        // 横向S从顺时针旋转90度再逆时针旋转90度
        first_tile = m_tile_vector.at(2);
        m_next_tile_vector.push_back(first_tile);
        m_next_tile_vector.push_back(base_tile);
        third_tile->setAbsoluteCoordinate(base_tile_x-2*g_tile_length, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(third_tile);
        forth_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    default:
        ERRORLOG("getNextTilesInfo||unknown m_current_shape||m_current_shape={}", m_current_shape);
        break;
    }
    return m_next_tile_vector;
}

void ShapeS::updateCurrentShape()
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