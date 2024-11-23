#include "shape_t.h"

// tile_board的第一层中间，用于新tile出现的定位
extern int g_tile_board_middle;
// tile边长
extern int g_tile_length;

ShapeT::ShapeT(const tile_sprites& type)
{
    resetShape(type);
    INFOLOG("ShapeT construct success");
}

ShapeT::~ShapeT()
{ 
    INFOLOG("ShapeT ~ShapeT success");
}

void ShapeT::resetShape(const tile_sprites& type, const int& defaultTileX, const int& defaultTileY)
{ 
    ShapeBase::resetShape(type, defaultTileX, defaultTileY);
    for (size_t i = 0; i < 3; i++)
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
    Tile* temp = new Tile(type);
    if(defaultTileX == -1)
    {
        temp->setRelativeCoordinate((g_tile_board_middle)*g_tile_length, 0);
    }
    else
    {
        temp->setAbsoluteCoordinate(defaultTileX+g_tile_length, defaultTileY);
    }
    m_tile_vector.push_back(temp);
}

std::vector<Tile*> ShapeT::getNextTilesInfo()
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
        // T形状从初始的丄顺时针旋转90度
        first_tile = m_tile_vector.at(3);
        m_next_tile_vector.push_back(first_tile);
        m_next_tile_vector.push_back(base_tile);
        third_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(third_tile);
        forth_tile = m_tile_vector.at(2);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    case 1:
        // T形状从丄顺时针旋转90度再顺时针旋转90度
        first_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(first_tile);
        m_next_tile_vector.push_back(base_tile);
        third_tile = m_tile_vector.at(3);
        m_next_tile_vector.push_back(third_tile);
        forth_tile = m_tile_vector.at(2);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    case 2:
        // T形状从丄顺时针旋转180度再顺时针旋转90度
        first_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y-g_tile_length);
        m_next_tile_vector.push_back(first_tile);
        m_next_tile_vector.push_back(base_tile);
        third_tile = m_tile_vector.at(3);
        m_next_tile_vector.push_back(third_tile);
        forth_tile = m_tile_vector.at(0);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    case 3:
        // T形状从丄顺时针旋转270度再顺时针旋转90度，即转回T的初始形状丄
        first_tile = m_tile_vector.at(3);
        m_next_tile_vector.push_back(first_tile);
        m_next_tile_vector.push_back(base_tile);
        third_tile->setAbsoluteCoordinate(base_tile_x+g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(third_tile);
        forth_tile = m_tile_vector.at(0);
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

void ShapeT::updateCurrentShape()
{
    // I只有两种形态
    switch (m_current_shape)
    {
    case 0:
        // T形状从初始的丄顺时针旋转90度
        m_current_shape = 1;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    case 1:
        // T形状从丄顺时针旋转90度再顺时针旋转90度
        m_current_shape = 2;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    case 2:
        // T形状从丄顺时针旋转180度再顺时针旋转90度
        m_current_shape = 3;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    case 3:
        // T形状从丄顺时针旋转270度再顺时针旋转90度，即转回T的初始形状丄
        m_current_shape = 0;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    default:
        ERRORLOG("updateCurrentShape||unknown m_current_shape||m_current_shape={}", m_current_shape);
        break;
    }
}