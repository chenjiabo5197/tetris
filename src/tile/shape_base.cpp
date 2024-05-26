#include "shape_base.h"

ShapeBase::ShapeBase(/* args */)
{
    m_down_rate_sum = 0;
}

ShapeBase::~ShapeBase()
{
}

std::vector<Tile*> ShapeBase::get_tiles_info()
{
    return m_tile_vector;
}

void ShapeBase::shape_change()
{

}

bool ShapeBase::shape_down(const float& down_rate)
{
    if (m_down_rate_sum < 1)
    {
        m_down_rate_sum += down_rate;
    }
    else if (m_down_rate_sum >= 1)
    {
        m_down_rate_sum = 0;
        for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
        {
            (*it)->tile_down();
        }
    }
}

bool ShapeBase::shape_left()
{
    for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    {
        (*it)->tile_left();
    }
}

bool ShapeBase::shape_right()
{
    for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    {
        (*it)->tile_right();
    }
}