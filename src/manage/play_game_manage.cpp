#include "play_game_manage.h"

// 主窗口
extern SDLWindow* g_main_window; 
// 普通字体
extern TTF_Font* g_normal_font;
// tile的全局加载
extern SDLTexture* g_tile_texture;

// tile每个区域
extern SDL_Rect g_tile_clips[TOTAL_TILE_SPRITES];

// 是否机器人先手
bool is_machine_first = false;

PlayGameManage::PlayGameManage(const Config& config)
{
    std::string temp;
    m_button_interval = config.Read("playchess_buttons_interval", 0);
    m_buttons_x = config.Read("playchess_buttons_x", 0);
    m_buttons_y = config.Read("playchess_buttons_y", 0);
    m_playchess_buttons[0] = new SDLButton(config, "back_menu", m_buttons_x, m_buttons_y);
    m_array_length = sizeof(m_playchess_buttons) / sizeof(m_playchess_buttons[0]);
    m_is_reset_single_player_chess_data_board = true;
    m_is_reset_two_players_chess_data_board = true;
    m_tiles_path = config.Read("tiles_resource_path", temp);
    m_tile_length = config.Read("tile_side_length", 0);
    m_tile_board_col_nums = config.Read("tile_board_width", 0);
    m_tile_board_row_nums = config.Read("tile_board_height", 0);
    m_tile_board = new TileBoard(config, m_tile_board_col_nums*m_tile_length, m_tile_board_row_nums*m_tile_length);
    DEBUGLOG("PlayGameManage construct success||button_interval={}||buttons_x={}||buttons_y={}||array_length={}", 
    m_button_interval, m_buttons_x, m_buttons_y, m_array_length);
}

PlayGameManage::~PlayGameManage()
{
    delete m_tile_board;
    DEBUGLOG("~PlayGameManage success||release resource");
}

void PlayGameManage::init()
{
    for (int i = 0; i < m_array_length; i++)
    {
        m_playchess_buttons[i]->initButtonCurrentSprite();
    }
    DEBUGLOG("init||init variable success");
    for (int i = 0; i < m_array_length; i++)
    {
        m_playchess_buttons[i]->loadResource(g_main_window->getWindow(), g_main_window->getRenderer());
    }
    DEBUGLOG("init||load resource success");
    g_tile_texture = new SDLTexture("tiles");
    if(!g_tile_texture->loadFromFile(g_main_window->getWindow(), g_main_window->getRenderer(), m_tiles_path))
    {        
        ERRORLOG("Failed to load g_tile_texture!"); 
    }
    DEBUGLOG("init||load g_tile_texture resource success");
    for (int i = 0; i < TOTAL_TILE_SPRITES; i++)
    {
        g_tile_clips[i].x = m_tile_length * i;
        g_tile_clips[i].y = 0;
        g_tile_clips[i].w = m_tile_length;
        g_tile_clips[i].h = m_tile_length;
    }
    INFOLOG("init||init success");
    Tile* temp = new Tile(m_array_length, TILE_RED, m_tile_board->get_left_top_coordinate());
    temp->set_coordinate(0, 0);
    m_tile_vector.push_back(temp);
    Tile* temp2 = new Tile(m_array_length, TILE_BLUE, m_tile_board->get_left_top_coordinate());
    temp2->set_coordinate(34, 0);
    m_tile_vector.push_back(temp2);
}

void PlayGameManage::startRender()
{
    for (int i = 0; i < m_array_length; i++)
    {
        m_playchess_buttons[i]->buttonRender(g_main_window->getRenderer());
    }
    m_tile_board->render();
    for (std::vector<Tile*>::iterator it=m_tile_vector.begin(); it < m_tile_vector.end(); it++) {
        (*it)->render();
    }
}

bool PlayGameManage::handleMouseClick(SDL_Event* event)
{
    return false;
}

void PlayGameManage::handleEvents(SDL_Event* event)
{
    // 遍历渲染当前按键的状态
    for (int i = 0; i < m_array_length; i++)
    {
        m_playchess_buttons[i]->handleButtonEvent(event);
    }
    // 检查返回主菜单键状态
    if (m_playchess_buttons[0]->getButtonCurrentSprite() == BUTTON_SPRITE_MOUSE_UP)
    {
        SDL_Event event;
        event.type = BACK_MANU_EVENT;
        SDL_PushEvent(&event);
        m_playchess_buttons[0]->initButtonCurrentSprite();
        INFOLOG("handleEvents||push event=BACK_MANU_EVENT");
    }
}

