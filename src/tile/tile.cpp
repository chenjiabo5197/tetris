#include "tile.h"

// 主窗口
extern SDLWindow* g_main_window; 

extern SDLTexture* g_tile_texture;

extern SDL_Rect g_tile_clips[TOTAL_TILE_SPRITES];

// tile边长
extern int tile_length;

// tileboard 区域
extern SDL_Rect tile_board_region;

Tile::Tile(const tile_sprites& type)
{
    //Get the offsets
    m_box.x = -1;
    m_box.y = -1;
    m_box.w = tile_length;
    m_box.h = tile_length;
    //Get the tile type
    m_type = type;

    m_offset_x = tile_board_region.x;
    m_offset_y = tile_board_region.y;

    INFOLOG("Tile construct success||m_box.w={}||m_box.h={}||m_offset_x={}||m_offset_y={}", m_box.w, m_box.h, m_offset_x, m_offset_y);
}

tile_sprites Tile::getType()
{
    return m_type;
}

SDL_Rect Tile::getBox()
{
    return m_box;
}

void Tile::render()
{
    if(g_tile_texture == nullptr)
    {
        ERRORLOG("render||g_tile_texture is nullptr");
        return;
    }
    if (m_box.x == -1 || m_box.y == -1)
    {
        ERRORLOG("render||m_box not set value");
        return;
    }
    g_tile_texture->render(g_main_window->getRenderer(), m_box.x, m_box.y, 1.0, &g_tile_clips[m_type]);
}

bool Tile::set_coordinate(const int& x, const int& y)
{
    m_box.x = x + m_offset_x;
    m_box.y = y + m_offset_y;
}

bool Tile::tile_down()
{
    if (m_box.y+tile_length >= tile_board_region.y+tile_board_region.h)
    {
        return false;
    }
    m_box.y = m_box.y + 1;
}

bool Tile::tile_left()
{
    if (m_box.x <= tile_board_region.x)
    {
        return false;
    }
    m_box.x = m_box.x - tile_length;
}

bool Tile::tile_right()
{
    if (m_box.x+tile_length >= tile_board_region.x+tile_board_region.w)
    {
        return false;
    }
    m_box.x = m_box.x + tile_length;
}