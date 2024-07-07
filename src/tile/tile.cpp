#include "tile.h"

// 主窗口
extern SDLWindow* g_main_window; 

extern SDLTexture* g_tile_texture;

extern SDL_Rect g_tile_clips[TOTAL_TILE_SPRITES];

// tileboard 区域
extern SDL_Rect g_tile_board_region;

// tile边长
extern int g_tile_length;

// tile原图的边长
extern int g_tile_resource_length;

Tile::Tile(const tile_sprites& type)
{
    //Get the offsets
    m_box.x = -1;
    m_box.y = -1;
    m_box.w = g_tile_length;
    m_box.h = g_tile_length;
    //Get the tile type
    m_type = type;

    m_offset_x = g_tile_board_region.x;
    m_offset_y = g_tile_board_region.y;

    INFOLOG("Tile construct success||m_box.w={}||m_box.h={}||m_offset_x={}||m_offset_y={}", m_box.w, m_box.h, m_offset_x, m_offset_y);
}

Tile::~Tile()
{
    INFOLOG("Tile ~Tile success");
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
    g_tile_texture->render(g_main_window->getRenderer(), m_box.x, m_box.y, static_cast<float>(g_tile_length)/g_tile_resource_length, &g_tile_clips[m_type]);
}

void Tile::setRelativeCoordinate(const int& x, const int& y)
{
    m_box.x = x + m_offset_x;
    m_box.y = y + m_offset_y;
}

void Tile::setAbsoluteCoordinate(const int& x, const int& y)
{
    m_box.x = x;
    m_box.y = y;
}

bool Tile::tileDown(const int& rate)
{
    /*
        注意：
            下落速度必须为 g_tile_length 的约数或者倍数，否则会出现tile重叠问题
    */
    m_box.y = m_box.y + rate;
}

bool Tile::tileLeft()
{
    m_box.x = m_box.x - g_tile_length;
}

bool Tile::tileRight()
{
    m_box.x = m_box.x + g_tile_length;
}

int Tile::updateTileRow()
{
    for (size_t i = 0; i < g_tile_board_region.h/g_tile_length; i++)
    {
        if (m_box.y == g_tile_board_region.y+i*g_tile_length)
        {
            DEBUGLOG("updateTileRow||tile row={}", i);
            return i;
        }
    }
    ERRORLOG("updateTileRow||tile row not match");
    return -1;
}

int Tile::updateTileCol()
{
    for (size_t i = 0; i < g_tile_board_region.w/g_tile_length; i++)
    {
        if (m_box.x == g_tile_board_region.x+i*g_tile_length)
        {
            DEBUGLOG("updateTileCol||tile col={}", i);
            return i;
        }
    }
    ERRORLOG("updateTileCol||tile col not match");
    return -1;
}

void Tile::updateTileRowCol()
{
    int temp_col = updateTileCol();
    if (temp_col != -1)
    {
        m_tile_col = temp_col;
        DEBUGLOG("updateTileRowCol||m_tile_col={}", m_tile_col);
    }
    else
    {
        m_tile_col = -1;
        ERRORLOG("updateTileRowCol||tile col not match");
    }
    int temp_row = updateTileRow();
    if (temp_col != -1)
    {
        m_tile_row = temp_row;
        DEBUGLOG("updateTileRowCol||m_tile_row={}", m_tile_row);
    }
    else
    {
        m_tile_row = -1;
        ERRORLOG("updateTileRowCol||tile row not match");
    }
}

int Tile::getTileRow()
{
    return m_tile_row;
}

int Tile::getTileCol()
{
    return m_tile_col;
}
