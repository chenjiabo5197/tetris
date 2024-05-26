#include "tile.h"

// 主窗口
extern SDLWindow* g_main_window; 

extern SDLTexture* g_tile_texture;

extern SDL_Rect g_tile_clips[TOTAL_TILE_SPRITES];

// tile边长
extern int tile_length;

// 每个tile1的偏移量
extern std::pair<int, int> tile_offset;

Tile::Tile(const tile_sprites& type)
{
    //Get the offsets
    m_box.x = -1;
    m_box.y = -1;
    m_box.w = tile_length;
    m_box.h = tile_length;
    //Get the tile type
    m_type = type;

    m_offset_x = tile_offset.first;
    m_offset_y = tile_offset.second;

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