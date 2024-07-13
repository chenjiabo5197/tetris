#include "shape_base.h"

ShapeBase::ShapeBase(/* args */)
{
    m_down_rate_sum = 0;
    INFOLOG("ShapeBase construct success");
}

ShapeBase::~ShapeBase()
{
    INFOLOG("ShapeBase ~ShapeBase success");
}

ShapeBase::ShapeBase(const ShapeBase& shape)
{
    for (auto it = shape.m_tile_vector.begin(); it != shape.m_tile_vector.end(); it++)
    {
        Tile* temp_tile = new Tile(**it);
        m_tile_vector.push_back(temp_tile);
    }
    for (auto it = shape.m_next_tile_vector.begin(); it != shape.m_next_tile_vector.end(); it++)
    {
        Tile* temp_tile = new Tile(**it);
        m_next_tile_vector.push_back(temp_tile);
    }
    m_down_rate_sum = shape.m_down_rate_sum;
    m_current_shape = shape.m_current_shape;
}

std::vector<Tile*> ShapeBase::getTilesInfo() const
{
    // DEBUGLOG("ShapeBase||getTilesInfo");
    return m_tile_vector;
}

std::vector<Tile*> ShapeBase::getNextTilesInfo()
{
    INFOLOG("ShapeBase||getNextTilesInfo");
    return m_next_tile_vector;
}

void ShapeBase::shapeChange()
{
    DEBUGLOG("ShapeBase||shapeChange");
    m_tile_vector.clear();
    m_tile_vector.insert(m_tile_vector.end(), m_next_tile_vector.begin(), m_next_tile_vector.end());
}

bool ShapeBase::shapeDown(const float& down_rate)
{
    // DEBUGLOG("ShapeBase||shapeDown");
    // if (m_down_rate_sum < 1)
    // {
    //     m_down_rate_sum += down_rate;
    // }
    // else if (m_down_rate_sum >= 1)
    // {
    //     m_down_rate_sum = 0;
    //     for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    //     {
    //         (*it)->tileDown();
    //     }
    // }
    for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    {
        (*it)->tileDown(down_rate);
    }
}

bool ShapeBase::shapeLeft()
{
    DEBUGLOG("ShapeBase||shapeLeft");
    for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    {
        (*it)->tileLeft();
    }
}

bool ShapeBase::shapeRight()
{
    DEBUGLOG("ShapeBase||shapeRight");
    for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    {
        (*it)->tileRight();
    }
}

void ShapeBase::render()
{
    for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    {
        (*it)->render();
    }
}

void ShapeBase::updateCurrentShape()
{
    DEBUGLOG("ShapeBase||updateCurrentShape");
}