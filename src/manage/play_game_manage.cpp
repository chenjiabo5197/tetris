#include "play_game_manage.h"

// 主窗口
extern SDLWindow* g_main_window; 
// 普通字体
extern TTF_Font* g_normal_font;
// tile的全局加载
extern SDLTexture* g_tile_texture;

// tile每个区域
extern SDL_Rect g_tile_clips[TOTAL_TILE_SPRITES];

// tile边长
extern int tile_length;

// tileboard 区域
extern SDL_Rect tile_board_region;

// tile_board的第一层中间，用于新tile出现的定位
extern int tile_board_middle;

ShapeBase* shape_base = nullptr;

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
    tile_length = config.Read("tile_side_length", 0);
    m_tile_board_col_nums = config.Read("tile_board_width", 0);
    m_tile_board_row_nums = config.Read("tile_board_height", 0);
    tile_board_middle = m_tile_board_col_nums / 2 + 1;
    m_tile_board = new TileBoard(config, m_tile_board_col_nums*tile_length, m_tile_board_row_nums*tile_length);
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
        g_tile_clips[i].x = tile_length * i;
        g_tile_clips[i].y = 0;
        g_tile_clips[i].w = tile_length;
        g_tile_clips[i].h = tile_length;
    }
    INFOLOG("init||init success");
    tile_board_region = m_tile_board->get_left_top_coordinate();
    // Tile* temp = new Tile(TILE_ORANGE);
    // temp->set_coordinate(0, 0);
    // m_tile_vector.push_back(temp);
    shape_base = new ShapeL(TILE_ORANGE);
    auto temp_vector = shape_base->get_tiles_info();
    m_tile_vector.insert(m_tile_vector.end(), temp_vector.begin(), temp_vector.end());
    // TODO 为什么下面的会出core
    // m_tile_vector.insert(m_tile_vector.end(), shape_base->get_tiles_info().begin(), shape_base->get_tiles_info().end());
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
        shape_base->shape_down(0.3);
    }
}

bool PlayGameManage::handleMouseClick(SDL_Event* event)
{
    return false;
}

void PlayGameManage::handleEvents(SDL_Event* event)
{
    // switch(event->key.keysym.sym)
    // {
    //     // 识别的是键盘的上下左右四个方向按键
    //     case SDLK_UP:   
    //         shape_base->shape_change();
    //         break;
    //     case SDLK_DOWN:
    //         shape_base->shape_down(100);
    //         break;
    //     case SDLK_LEFT:
    //         shape_base->shape_left();
    //         break;
    //     case SDLK_RIGHT:
    //         shape_base->shape_right();
    //         break;
    //     default:
    //         ERRORLOG("handleEvents||unndefined key");
    //         break;
    // }
    const Uint8* currentKeyStates = SDL_GetKeyboardState( nullptr );
    if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
        shape_base->shape_change();
    }
    else if( currentKeyStates[ SDL_SCANCODE_DOWN ] )
    {
        shape_base->shape_down(100);
    }
    else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
        shape_base->shape_left();
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
        shape_base->shape_right();
    }
    else
    {
        ERRORLOG("handleEvents||unndefined key");
    }
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

