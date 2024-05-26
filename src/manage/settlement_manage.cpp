#include "settlement_manage.h"

// 主窗口
extern SDLWindow* g_main_window; 
// 艺术字体 行楷
extern TTF_Font* g_art_font;
// 普通字体
extern TTF_Font* g_normal_font;

SettlementManage::SettlementManage(const Config& config)
{
    std::string temp;
    m_buttons_x = config.Read("settlement_buttons_x", 0);
    m_buttons_y = config.Read("settlement_buttons_y", 0);
    m_button_interval = config.Read("settlement_buttons_interval", 0);
    m_settlement_buttons[0] = new SDLButton(config, "again_game", m_buttons_x, m_buttons_y-m_button_interval);
    m_settlement_buttons[1] = new SDLButton(config, "back_menu", m_buttons_x, m_buttons_y);
    m_array_length = sizeof(m_settlement_buttons) / sizeof(m_settlement_buttons[0]);
    DEBUGLOG("SettlementManage construct success||button_interval={}||buttons_x={}||buttons_y={}||array_length={}", 
    m_button_interval, m_buttons_x, m_buttons_y, m_array_length);
}

SettlementManage::~SettlementManage()
{
    DEBUGLOG("~SettlementManage success||release resource");
}

void SettlementManage::init()
{
    for (int i = 0; i < m_array_length; i++)
    {
        m_settlement_buttons[i]->initButtonCurrentSprite();
    }
    INFOLOG("init||init variable success");
    for (int i = 0; i < m_array_length; i++)
    {
        m_settlement_buttons[i]->loadResource(g_main_window->getWindow(), g_main_window->getRenderer());
    }
    INFOLOG("loadResource||load resource success");
}

void SettlementManage::startRender()
{
    for (int i = 0; i < m_array_length; i++)
    {
        m_settlement_buttons[i]->buttonRender(g_main_window->getRenderer());
    }
    // DEBUGLOG("startRender");
}

void SettlementManage::handleEvents(SDL_Event* event)
{
    for (int i = 0; i < m_array_length; i++)
    {
        m_settlement_buttons[i]->handleButtonEvent(event);
    }
    if (m_settlement_buttons[0]->getButtonCurrentSprite() == BUTTON_SPRITE_MOUSE_UP)
    {
    }
    if (m_settlement_buttons[1]->getButtonCurrentSprite() == BUTTON_SPRITE_MOUSE_UP)
    {
        SDL_Event event;
        event.type = BACK_MANU_EVENT;
        SDL_PushEvent(&event);
        m_settlement_buttons[1]->initButtonCurrentSprite();
        INFOLOG("handleEvents||push event=BACK_MANU_EVENT");
    }
}

void SettlementManage::setFontCoordinate(const int& x, const int& y)
{
    m_font_x = x;
    m_font_y = y;
    INFOLOG("setFontCoordinate||font_x={}||font_y={}", m_font_x, m_font_y);
}

void SettlementManage::setInterfaceRenderType(const interface_kind_type& type)
{

}
