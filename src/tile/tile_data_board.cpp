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
    m_data_board_ttf = new SDLTTF("tetris_data_ttf");
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
    // 渲染右上角解释窗口
    // 默认字体黑色
    SDL_Color color = {0, 0, 0, 0};
    SDL_Color current_color = {0, 255, 0, 0};
    // 窗口头显示时间
    std::stringstream time_text;
    time_text.str("");
    //  除1000，是因为需要的是秒，而每秒有1000毫秒,小数点后取1位小数
    time_text << std::setiosflags(std::ios::fixed) << std::setprecision(1) << (m_top_timer->timerGetTicks() / 1000.f); 
    this->renderText("对局开始(s): ", g_normal_font, color, m_data_board_x+60, m_data_board_y-150, 0.6);  
    this->renderText(time_text.str(), g_normal_font, color,m_data_board_x+50, m_data_board_y-110, 0.6);  //时间信息
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
    m_top_timer->timerStart();
    INFOLOG("startSingleGame||start timer||type={}");
}

void TileDataBoard::pauseTimer()
{
    m_top_timer->timerPause();
    INFOLOG("stopTimer");
}



