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

std::vector<Tile*> ShapeBase::getTilesInfo() const
{
    return m_tile_vector;
}

void ShapeBase::shapeChange()
{
    DEBUGLOG("ShapeBase||shapeChange");
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
        (*it)->tileDown();
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