#include "tile_board.h"

// 主窗口
extern SDLWindow* g_main_window; 
// 艺术字体 行楷
extern TTF_Font* g_art_font;
// 普通字体
extern TTF_Font* g_normal_font;

TileBoard::TileBoard(const Config& config, const int& width, const int& height)
{
    m_width = width;
    m_height = height;
    m_center_x = config.Read("tile_board_center_x", 0);
    m_center_y = config.Read("tile_board_center_y", 0);
    INFOLOG("TileBoard construct success||m_width={}||m_height={}||m_center_x={}||m_center_y={}", 
	m_width, m_height, m_center_x, m_center_y);
}

TileBoard::~TileBoard()
{
    INFOLOG("~TileBoard success||release resource");
}

void TileBoard::render()
{
    SDL_Rect tile_board = {m_center_x-m_width/2, m_center_y-m_height/2, m_width, m_height};
    SDL_SetRenderDrawColor(g_main_window->getRenderer(), 0x00, 0x00, 0x00, 0xFF);        
    SDL_RenderFillRect(g_main_window->getRenderer(), &tile_board);
}

SDL_Rect TileBoard::getLeftTopCoordinate()
{
    SDL_Rect tile_board = {m_center_x-m_width/2, m_center_y-m_height/2, m_width, m_height};
    return tile_board;
}
