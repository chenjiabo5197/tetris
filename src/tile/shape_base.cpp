#include "shape_base.h"

ShapeBase::ShapeBase(/* args */)
{
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

bool ShapeBase::shape_down()
{
    for (auto it = m_tile_vector.begin(); it != m_tile_vector.end(); it++)
    {
        (*it)->tile_down();   
    }
}