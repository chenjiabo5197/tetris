#include "shape_j.h"

// tile_board的第一层中间，用于新tile出现的定位
extern int g_tile_board_middle;
// tile边长
extern int g_tile_length;

ShapeJ::ShapeJ(const tile_sprites& type)
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
    m_current_shape = 0;
    INFOLOG("ShapeJ construct success");
}

ShapeJ::~ShapeJ()
{ 
    INFOLOG("ShapeJ ~ShapeJ success");
}

std::vector<Tile*> ShapeJ::getNextTilesInfo()
{
    // 先清空m_next_tile_vector
    m_next_tile_vector.clear();
    // 第三块tile不变，为基准
    auto base_tile = m_tile_vector.at(2);
    tile_sprites base_type = base_tile->getType();
    int base_tile_x = base_tile->getBox().x;
    int base_tile_y = base_tile->getBox().y;
    auto first_tile = new Tile(base_type);
    auto second_tile = new Tile(base_type);
    auto forth_tile = new Tile(base_type);
    // I只有两种形态
    switch (m_current_shape)
    {
    case 0:
        // 从J的初始形态(竖折)顺时针旋转90度
        first_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y-g_tile_length);
        m_next_tile_vector.push_back(first_tile);
        second_tile->setAbsoluteCoordinate(base_tile_x+g_tile_length, base_tile_y-g_tile_length);
        m_next_tile_vector.push_back(second_tile);
        m_next_tile_vector.push_back(base_tile);
        forth_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    case 1:
        // 从J的初始形态(竖折)顺时针旋转90度再旋转90度
        first_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(first_tile);
        second_tile->setAbsoluteCoordinate(base_tile_x+g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(second_tile);
        m_next_tile_vector.push_back(base_tile);
        forth_tile->setAbsoluteCoordinate(base_tile_x+g_tile_length, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    case 2:
        // 从J的初始形态(竖折)顺时针旋转180度再旋转90度，变为J
        first_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(first_tile);
        second_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y+g_tile_length);
        m_next_tile_vector.push_back(second_tile);
        m_next_tile_vector.push_back(base_tile);
        forth_tile->setAbsoluteCoordinate(base_tile_x, base_tile_y-g_tile_length);
        m_next_tile_vector.push_back(forth_tile);
        for (auto i = m_next_tile_vector.begin(); i != m_next_tile_vector.end(); i++)
        {
            DEBUGLOG("x={}||y={}", (*i)->getBox().x, (*i)->getBox().y);
        }
        break;
    case 3:
        // 从J的初始形态(竖折)顺时针旋转270度再旋转90度，变为J的初始形态(竖折)
        first_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y-g_tile_length);
        m_next_tile_vector.push_back(first_tile);
        second_tile->setAbsoluteCoordinate(base_tile_x-g_tile_length, base_tile_y);
        m_next_tile_vector.push_back(second_tile);
        m_next_tile_vector.push_back(base_tile);
        forth_tile->setAbsoluteCoordinate(base_tile_x+g_tile_length, base_tile_y);
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

void ShapeJ::updateCurrentShape()
{
    // I只有两种形态
    switch (m_current_shape)
    {
    case 0:
        // 从J的初始形态(竖折)顺时针旋转90度
        m_current_shape = 1;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    case 1:
        // 从J的初始形态(竖折)顺时针旋转90度再旋转90度
        m_current_shape = 2;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    case 2:
        // 从J的初始形态(竖折)顺时针旋转180度再旋转90度，变为J
        m_current_shape = 3;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    case 3:
        // 从J的初始形态(竖折)顺时针旋转270度再旋转90度，变为J的初始形态(竖折)
        m_current_shape = 0;
        INFOLOG("updateCurrentShape||m_current_shape={}", m_current_shape);
        break;
    default:
        ERRORLOG("updateCurrentShape||unknown m_current_shape||m_current_shape={}", m_current_shape);
        break;
    }
}