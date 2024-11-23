#include "tile_data_board.h"

// 主窗口
extern SDLWindow* g_main_window; 
// 艺术字体 行楷
extern TTF_Font* g_art_font;
// 普通字体
extern TTF_Font* g_normal_font;

TileDataBoard::TileDataBoard(const Config& config)
{
    m_top_timer = new SDLTimer("top_timer");
    m_data_board_x = config.Read("data_board_x", 0);
    m_data_board_y = config.Read("data_board_y", 0);
    INFOLOG("TileDataBoard construct success||data_board_x={}||data_board_y={}", 
    m_data_board_x, m_data_board_y);
}

TileDataBoard::~TileDataBoard()
{
    delete m_data_board_ttf;
    delete m_top_timer;
    INFOLOG("~ChessDataBoard success||release resources");
}

void TileDataBoard::init()
{
    INFOLOG("init||ChessDataBoard init success||load resource success");
}

void TileDataBoard::initDataBoard()
{
    INFOLOG("initDataBoard success||chess_color_type={}");
}

void TileDataBoard::resetDataBoard()
{
    INFOLOG("resetDataBoard");
}

void TileDataBoard::render()
{
}

void TileDataBoard::renderText(const std::string& texture_text, TTF_Font* texture_ttf, SDL_Color color, const int& x, const int& y, const float& multiple)
{
	m_data_board_ttf->loadRenderText(g_main_window->getRenderer(), texture_ttf, texture_text, color);
	m_data_board_ttf->ttfRender(g_main_window->getRenderer(), x, y, multiple);
}

void TileDataBoard::updateScoreInfo()
{
}

void TileDataBoard::startSingleGame()
{
    INFOLOG("startSingleGame||start timer||type={}");
}



