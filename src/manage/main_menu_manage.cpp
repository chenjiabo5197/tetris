#include "main_menu_manage.h"

// 主窗口
extern SDLWindow* g_main_window; 

MainMenuManage::MainMenuManage(const Config& config)
{
    m_buttons_x = config.Read("g_main_window_screen_width", 0) / 2;// TODO 新建优化
    m_buttons_y = config.Read("g_main_window_screen_height", 0) / 2;
    m_button_interval = config.Read("main_menu_buttons_interval", 0);
    m_main_menu_buttons[0] = new SDLButton(config, "start_game", m_buttons_x, m_buttons_y-m_button_interval);
    m_main_menu_buttons[1] = new SDLButton(config, "best_scores", m_buttons_x, m_buttons_y);
    m_main_menu_buttons[2] = new SDLButton(config, "exit_game", m_buttons_x, m_buttons_y+m_button_interval);
    backMenuButton = new SDLButton(config, "back_menu", m_buttons_x+180, m_buttons_y+230);
    m_array_length = sizeof(m_main_menu_buttons) / sizeof(m_main_menu_buttons[0]);
    m_is_show_best_score = false;
    m_data_board_ttf = new SDLTTF("tetris_data_ttf");
    DEBUGLOG("MainMenuManage construct success||button_interval={}||buttons_x={}||buttons_y={}||array_length={}", 
    m_button_interval, m_buttons_x, m_buttons_y, m_array_length);
}

MainMenuManage::~MainMenuManage()
{
    delete m_data_board_ttf;
    DEBUGLOG("~MainMenuManage success||release resource");
}

void MainMenuManage::init()
{
    for (int i = 0; i < m_array_length; i++)
    {
        m_main_menu_buttons[i]->initButtonCurrentSprite();
    }
    backMenuButton->initButtonCurrentSprite();
    INFOLOG("init||init variable success");
    for (int i = 0; i < m_array_length; i++)
    {
        m_main_menu_buttons[i]->loadResource(g_main_window->getWindow(), g_main_window->getRenderer());
    }
    backMenuButton->loadResource(g_main_window->getWindow(), g_main_window->getRenderer());
    INFOLOG("loadResource||load resource success");
}

void MainMenuManage::startRender()
{
    if (m_is_show_best_score)
    {
        bestScoreRender();
    }
    else
    {
        for (int i = 0; i < m_array_length; i++)
        {
            m_main_menu_buttons[i]->buttonRender(g_main_window->getRenderer());
        }
    }
    // DEBUGLOG("startRender");
}

// TODO 查看排行榜
void MainMenuManage::handleEvents(SDL_Event* event)
{
    switch (event->type)
    {
    case BEST_SCORES_EVENT:
        this->showBestScore();
        break;
    default:
        if(m_is_show_best_score)
        {
            backMenuButton->handleButtonEvent(event);
        }
        else
        {
            for (int i = 0; i < m_array_length; i++)
            {
                m_main_menu_buttons[i]->handleButtonEvent(event);
            }
        }
        break;
    }
    SDL_Event pushEvent;
    if (m_main_menu_buttons[0]->getButtonCurrentSprite() == BUTTON_SPRITE_MOUSE_UP)
    {
        pushEvent.type = START_GAME_EVENT;
        SDL_PushEvent(&pushEvent);
        m_main_menu_buttons[0]->initButtonCurrentSprite();
        INFOLOG("handleEvents||push event=START_GAME_EVENT");
    }
    if (m_main_menu_buttons[1]->getButtonCurrentSprite() == BUTTON_SPRITE_MOUSE_UP)
    {
        pushEvent.type = BEST_SCORES_EVENT;
        SDL_PushEvent(&pushEvent);
        m_main_menu_buttons[1]->initButtonCurrentSprite();
        INFOLOG("handleEvents||push event=BEST_SCORES_EVENT");
    }
    if (m_main_menu_buttons[2]->getButtonCurrentSprite() == BUTTON_SPRITE_MOUSE_UP)
    {
        pushEvent.type = EXIT_GAME_EVENT;
        SDL_PushEvent(&pushEvent);
        INFOLOG("handleEvents||push event=EXIT_GAME_EVENT");
    }
    // 检查返回主菜单键状态
    if (backMenuButton->getButtonCurrentSprite() == BUTTON_SPRITE_MOUSE_UP)
    {
        pushEvent.type = BACK_MANU_EVENT;
        SDL_PushEvent(&pushEvent);
        backMenuButton->initButtonCurrentSprite();
        m_is_show_best_score = false;
        INFOLOG("handleEvents||push event=BACK_MANU_EVENT");
    }
}

void MainMenuManage::showBestScore()
{
    DEBUGLOG("showBestScore||show best score");
    m_is_show_best_score = true;
    bestScoreVector = initBestScores();
}

void MainMenuManage::bestScoreRender()
{
    SDL_Rect bestScore = {m_buttons_x-185, m_buttons_y-250, 350, 450};
    SDL_SetRenderDrawColor(g_main_window->getRenderer(), 0xff, 0xff, 0xff, 0xFF);        
    SDL_RenderFillRect(g_main_window->getRenderer(), &bestScore);
    backMenuButton->buttonRender(g_main_window->getRenderer());
    SDL_Color color = {0, 0, 0, 0};  // 黑色字体
    this->renderText("姓名", g_normal_font, color, m_buttons_x-150, m_buttons_y-240, 0.5);
    this->renderText("分数", g_normal_font, color, m_buttons_x-60, m_buttons_y-240, 0.5);  
    this->renderText("时间", g_normal_font, color, m_buttons_x+60, m_buttons_y-240, 0.5);
    for (size_t i = 0; i < bestScoreVector.size(); i++)
    {
        this->renderText(bestScoreVector[i].userName, g_normal_font, color, m_buttons_x-150, m_buttons_y-215+35*i, 0.3);
        this->renderText(bestScoreVector[i].userScore, g_normal_font, color, m_buttons_x-60, m_buttons_y-215+35*i, 0.3);  
        this->renderText(bestScoreVector[i].creatTime, g_normal_font, color, m_buttons_x+60, m_buttons_y-215+35*i, 0.3);  
    }
    
}

void MainMenuManage::renderText(const std::string& texture_text, TTF_Font* texture_ttf, SDL_Color color, const int& x, const int& y, const float& multiple)
{
	m_data_board_ttf->loadRenderText(g_main_window->getRenderer(), texture_ttf, texture_text, color);
	m_data_board_ttf->ttfRender(g_main_window->getRenderer(), x, y, multiple);
}

