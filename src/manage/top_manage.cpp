/*============================================
* Author: chenjiabo
* E-mail: chen_wangyi666@163.com
* Date: 2024-1-3
* Description: This is managevent.cpp file
* Copyright (c) 2024, All rights reserved
=============================================*/
#include "top_manage.h"

// 按键选择音效
extern Mix_Chunk* g_select_button_sound;
// 主窗口
extern SDLWindow* g_main_window; 
// 普通字体
extern TTF_Font* g_normal_font;

TopManage::TopManage(const Config& config)
{
    setRendererType(DEFAULT_INTERFACE);
    std::string temp;
    m_normal_ttf_path = config.Read("ttf_font_path", temp);
    m_normal_ttf_ptsize = config.Read("ttf_font_ptsize", 0);
    m_main_menu_manage = new MainMenuManage(config);
    m_play_game_manage = new PlayGameManage(config);
    m_settlement_manage = new SettlementManage(config);
    g_main_window = new SDLWindow(config, "g_main_window");
    DEBUGLOG("Manage construct success||render_type={}||normal_ttf_resource_path={}||normal_ttf_ptsize={}", 
    (int)m_render_type, m_normal_ttf_path, m_normal_ttf_ptsize);
}

TopManage::~TopManage()
{
    delete m_main_menu_manage;
    delete m_settlement_manage;
    delete m_play_game_manage;
    // delete g_main_window;
    DEBUGLOG("~Manage success||release resource");
}

void TopManage::start()
{
    this->setRendererType(MAIN_MENU_INTERFACE);
    //Start up SDL and create window
    if(!this->initRender())
    {
        ERRORLOG("Failed to initialize!");
        return;
    }
    //Hack to get window to stay up
    SDL_Event event;
    bool quit = false;
    setRendererType(MAIN_MENU_INTERFACE);
    //While application is running
    while(!quit)
    {
        //Handle events on queue
        while(SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
            case SDL_QUIT:
            case EXIT_GAME_EVENT:
                quit = true;
                break;
            case START_GAME_EVENT:
                setRendererType(PLAY_GAME_INTERFACE);
                m_play_game_manage->resetGame();
                break;
            case BACK_MANU_EVENT:
                setRendererType(MAIN_MENU_INTERFACE);
                break;
            default:  // 其他事件，鼠标移动，点击等事件
                switch (m_render_type)
                {
                case MAIN_MENU_INTERFACE:
                    m_main_menu_manage->handleEvents(&event);
                    break;
                case PLAY_GAME_INTERFACE:
                    m_play_game_manage->handleEvents(&event);
                    break;
                default:
                    break;
                }
                break;
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor(g_main_window->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(g_main_window->getRenderer());
        g_main_window->renderBackground();
        switch (m_render_type)
        {
        case MAIN_MENU_INTERFACE:
            m_main_menu_manage->startRender();
            break;
        case PLAY_GAME_INTERFACE:
            m_play_game_manage->startRender();
            break;
        default:
            break;
        }
        //Update screen
        SDL_RenderPresent(g_main_window->getRenderer());
    }
    //Free resources and close SDL
    this->closeRender();
}

bool TopManage::initRender()
{
    //Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0)
    {
        ERRORLOG("SDL could not initialize||SDL_Error: ", SDL_GetError());
        return false;
    }
    DEBUGLOG("SDL initialize success!");
    //Set texture filtering to linear
    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        WARNLOG("Warning: Linear texture filtering not enabled!");
    }
    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags) & imgFlags))
    {
        ERRORLOG("SDL_image could not initialize||SDL_image Error:", IMG_GetError());
        return false;
    }
    DEBUGLOG("SDL_image initialize success");
    //Initialize SDL_ttf
    if(TTF_Init() == -1)
    {
        ERRORLOG("SDL_ttf could not initialize||SDL_ttf Error:", TTF_GetError());
        return false;
    }
    DEBUGLOG("SDL_ttf initialize success");
    //Initialize SDL_mixer
    /*
    Mix_OpenAudio,第一个参数设置声音频率，44100 是标准频率，适用于大多数系统。
    第二个参数决定采样格式，这里使用默认格式。第三个参数是硬件声道数，这里使用 2 个声道作为立体声声道。
    最后一个参数是采样大小，它决定了播放声音时使用的音块大小。这里使用的是 2048 字节（又称 2 千字节），但要尽量减少播放声音时的延迟，可能需要尝试使用这个值。
    */
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0)
    {
        ERRORLOG("SDL_mixer could not initialize! SDL_mixer Error={}", Mix_GetError());
        return false;
    }
    DEBUGLOG("SDL_mixer initialize success");
    INFOLOG("initRender success!");
    if(!this->loadResource())
    {
        return false;
    }
    return true;
}

bool TopManage::loadResource()
{
    //使用 TTF_OpenFont 加载字体。这需要输入字体文件的路径和要渲染的点尺寸
    g_normal_font = TTF_OpenFont(m_normal_ttf_path.c_str(), m_normal_ttf_ptsize);
    if(g_normal_font == nullptr)
    {
        ERRORLOG("Failed to load {} font! SDL_ttf Error={}", m_normal_ttf_path, TTF_GetError());
        return false;
    }
    DEBUGLOG("Create font success!");
    g_select_button_sound = Mix_LoadWAV("resources/select_button.wav");
    if(g_select_button_sound == nullptr)
    {
        ERRORLOG("Failed to load g_select_button_sound sound effect! SDL_mixer Error={}", Mix_GetError());
        return false;
    }
    DEBUGLOG("load g_select_button_sound success!");
    // TODO 优化加载，默认不用加载后面用不到的管理页面
    g_main_window->init();
    m_main_menu_manage->init();
    m_settlement_manage->init();
    m_play_game_manage->init();
    INFOLOG("loadResource success!");
    return true;
}

void TopManage::closeRender()
{
    TTF_CloseFont(g_normal_font);
    g_normal_font = nullptr;
    Mix_FreeChunk(g_select_button_sound);
    g_select_button_sound = nullptr;
    g_main_window->free();
    g_main_window = nullptr;

    //Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    INFOLOG("closeRender||close render, quit sdl");
}

void TopManage::setRendererType(const interface_kind_type& render_type)
{
    m_render_type = render_type;
    INFOLOG("setRendererType||set render_type={}", (int)render_type);
}


