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
extern int g_tile_length;
// tile原图的边长
extern int g_tile_resource_length;

// tileboard 区域
extern SDL_Rect g_tile_board_region;

// tile_board的第一层中间，用于新tile出现的定位
extern int g_tile_board_middle;

ShapeBase* shape_base = nullptr;

PlayGameManage::PlayGameManage(const Config& config)
{
    std::string temp;
    m_button_interval = config.Read("playchess_buttons_interval", 0);
    m_buttons_x = config.Read("playchess_buttons_x", 0);
    m_buttons_y = config.Read("playchess_buttons_y", 0);
    m_playchess_buttons[0] = new SDLButton(config, "back_menu", m_buttons_x, m_buttons_y);
    m_array_length = sizeof(m_playchess_buttons) / sizeof(m_playchess_buttons[0]);
    m_tiles_path = config.Read("tiles_resource_path", temp);
    g_tile_resource_length = config.Read("tile_resource_side_length", 0);
    g_tile_length = config.Read("tile_side_length", 0);
    m_tile_board_col_nums = config.Read("tile_board_width", 0);
    m_tile_board_row_nums = config.Read("tile_board_height", 0);
    g_tile_board_middle = m_tile_board_col_nums / 2;
    m_tile_board = new TileBoard(config, m_tile_board_col_nums*g_tile_length, m_tile_board_row_nums*g_tile_length);
    m_last_shape_index = -1;
    m_last_tile_sprite_index = -1;
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
        g_tile_clips[i].x = g_tile_resource_length * i;
        g_tile_clips[i].y = 0;
        g_tile_clips[i].w = g_tile_resource_length;
        g_tile_clips[i].h = g_tile_resource_length;
    }
    INFOLOG("init||init success");
    g_tile_board_region = m_tile_board->getLeftTopCoordinate();
    auto rand_tile_sprite = nextTileSprite();
    shape_base = nextShape(rand_tile_sprite);
    // Tile* temp = new Tile(TILE_ORANGE);
    // temp->setRelativeCoordinate(0, 0);
    // m_tile_vector.push_back(temp);
    // shape_base = new ShapeI(TILE_ORANGE);
    // auto temp_vector = shape_base->getTilesInfo();
    // m_tile_vector.insert(m_tile_vector.end(), temp_vector.begin(), temp_vector.end());
    // TODO 为什么下面的会出core
    // m_tile_vector.insert(m_tile_vector.end(), shape_base->getTilesInfo().begin(), shape_base->getTilesInfo().end());
}

void PlayGameManage::startRender()
{
    if (isCanDown(*shape_base))
    {
        shape_base->shapeDown(1);
    }
    else
    {
        // TODO 回收内存
        // delete shape_base;
        auto temp_vector = shape_base->getTilesInfo();
        m_tile_vector.insert(m_tile_vector.end(), temp_vector.begin(), temp_vector.end());
        std::set<int> row_set;
        for (std::vector<Tile*>::iterator it=temp_vector.begin(); it < temp_vector.end(); it++)
        {
            (*it)->updateTileRowCol();
            row_set.insert((*it)->getTileRow());
        }
        for (auto it = row_set.begin(); it != row_set.end(); it++)
        {
            updateEliminate(*it);
        }
        
        shape_base = nullptr;
        auto rand_tile_sprite = nextTileSprite();
        shape_base = nextShape(rand_tile_sprite);
    }
    for (int i = 0; i < m_array_length; i++)
    {
        m_playchess_buttons[i]->buttonRender(g_main_window->getRenderer());
    }
    m_tile_board->render();
    for (std::vector<Tile*>::iterator it=m_tile_vector.begin(); it < m_tile_vector.end(); it++) 
    {
        (*it)->render();
    }
    shape_base->render();
}

bool PlayGameManage::handleMouseClick(SDL_Event* event)
{
    return false;
}

void PlayGameManage::handleEvents(SDL_Event* event)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(nullptr);
    if(currentKeyStates[SDL_SCANCODE_UP])
    {
        if (isShapeCanChange(*shape_base))
        {
            shape_base->shapeChange();
            shape_base->updateCurrentShape();
        }
    }
    else if(currentKeyStates[SDL_SCANCODE_DOWN])
    {
        shape_base->shapeDown(distanceCanShapeDown(*shape_base));
    }
    else if(currentKeyStates[SDL_SCANCODE_LEFT])
    {
        if (isCanLeft(*shape_base))
        {
            shape_base->shapeLeft();
        }
    }
    else if(currentKeyStates[SDL_SCANCODE_RIGHT])
    {
        if (isCanRight(*shape_base))
        {
            shape_base->shapeRight();
        }
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

bool PlayGameManage::isCanDown(const ShapeBase& shape)
{
    auto tiles = shape.getTilesInfo();
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        // 判断当前tile是否越过tile_board底线
        if ((*it)->getBox().y+g_tile_length >= g_tile_board_region.y+g_tile_board_region.h)
        {
            ERRORLOG("isCanDown||tile_board down line");
            return false;
        }
        // 判断目前vector中tile会不会阻碍该tile下落
        for (auto it2 = m_tile_vector.begin(); it2 != m_tile_vector.end(); it2++)
        {
            // if((*it)->getBox().x == (*it2)->getBox().x && (*it)->getBox().y+g_tile_length >= (*it2)->getBox().y)  当此图形上方有tile时会误判，需修改
            // 先判断当前tile是否在图形的下面，在当前图形上面的tile不予考虑
            // if ((*it)->getBox().y >= (*it2)->getBox().y + g_tile_length)
            // {
            //     continue;
            // }
            if((*it)->getBox().x == (*it2)->getBox().x && (*it)->getBox().y+g_tile_length == (*it2)->getBox().y)
            {
                ERRORLOG("isCanDown||tile stop down line");
                return false;
            }
        }
    }
    return true;
}

bool PlayGameManage::isCanLeft(const ShapeBase& shape)
{
    auto tiles = shape.getTilesInfo();
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        // 判断当前tile是否越过tile_board左侧边界
        if ((*it)->getBox().x <= g_tile_board_region.x)
        {
            ERRORLOG("isCanLeft||tile_board left line");
            return false;
        }
        // 判断目前vector中tile会不会阻碍该tile左移
        for (auto it2 = m_tile_vector.begin(); it2 != m_tile_vector.end(); it2++)
        {
            // 图形中tile和vector中tile的位置
            if((((*it)->getBox().y + g_tile_length > (*it2)->getBox().y && (*it)->getBox().y < (*it2)->getBox().y ) || 
            ((*it)->getBox().y > (*it2)->getBox().y && (*it)->getBox().y < (*it2)->getBox().y + g_tile_length) ||
            ((*it)->getBox().y == (*it2)->getBox().y)) && (*it)->getBox().x == (*it2)->getBox().x+g_tile_length)
            {
                ERRORLOG("isCanLeft||tile stop left line");
                return false;
            }
        }
    }
    return true;
}

bool PlayGameManage::isCanRight(const ShapeBase& shape)
{
    auto tiles = shape.getTilesInfo();
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        // 判断当前tile是否越过tile_board右侧边界
        if ((*it)->getBox().x+g_tile_length >= g_tile_board_region.x+g_tile_board_region.w)
        {
            ERRORLOG("isCanRight||tile_board right line");
            return false;
        }
        // 判断目前vector中tile会不会阻碍该tile左移
        for (auto it2 = m_tile_vector.begin(); it2 != m_tile_vector.end(); it2++)
        {
            if((((*it)->getBox().y + g_tile_length > (*it2)->getBox().y && (*it)->getBox().y < (*it2)->getBox().y ) || 
            ((*it)->getBox().y > (*it2)->getBox().y && (*it)->getBox().y < (*it2)->getBox().y + g_tile_length) ||
            ((*it)->getBox().y == (*it2)->getBox().y)) && (*it)->getBox().x+g_tile_length == (*it2)->getBox().x)
            {
                ERRORLOG("isCanRight||tile stop right line");
                return false;
            }
        }
    }
    return true;
}

bool PlayGameManage::isShapeCanChange(ShapeBase& shape)
{
    auto tiles = shape.getNextTilesInfo();
    for (auto it = tiles.begin(); it != tiles.end(); it++)
    {
        // 判断当前tile是否越过tile_board底线
        if ((*it)->getBox().y+g_tile_length > g_tile_board_region.y+g_tile_board_region.h)
        {
            ERRORLOG("isShapeCanChange||tile_board down line");
            return false;
        }
        // 判断当前tile是否越过tile_board左侧边界
        if ((*it)->getBox().x < g_tile_board_region.x)
        {
            ERRORLOG("isShapeCanChange||tile_board left line");
            return false;
        }
        // 判断当前tile是否越过tile_board右侧边界
        if ((*it)->getBox().x+g_tile_length > g_tile_board_region.x+g_tile_board_region.w)
        {
            ERRORLOG("isShapeCanChange||tile_board right line");
            return false;
        }
        // 判断目前vector中tile与该tile有部分重叠区域
        for (auto it2 = m_tile_vector.begin(); it2 != m_tile_vector.end(); it2++)
        {
            if((((*it)->getBox().y + g_tile_length > (*it2)->getBox().y && (*it)->getBox().y < (*it2)->getBox().y ) || 
            ((*it)->getBox().y > (*it2)->getBox().y && (*it)->getBox().y < (*it2)->getBox().y + g_tile_length) ||
            ((*it)->getBox().y == (*it2)->getBox().y)) && 
            (((*it)->getBox().x + g_tile_length > (*it2)->getBox().x && (*it)->getBox().x < (*it2)->getBox().x ) || 
            ((*it)->getBox().x > (*it2)->getBox().x && (*it)->getBox().x < (*it2)->getBox().x + g_tile_length) ||
            ((*it)->getBox().x == (*it2)->getBox().x)))
            {
                ERRORLOG("isShapeCanChange||tile stop change");
                return false;
            }
        }
    }
    return true;
}


ShapeBase* PlayGameManage::nextShape(const tile_sprites& type)
{
    int rand_index = m_last_shape_index;
    do
    {
        rand_index = getRandomNum(0, 6);
        // rand_index = 0;
        DEBUGLOG("nextShape||rand_index={}", rand_index);
    } while (rand_index == m_last_shape_index);
    m_last_shape_index = rand_index;
    ShapeBase* rand_shape = nullptr;
    switch (rand_index)
    {
    case 0:
        rand_shape = new ShapeI(type);
        break;
    case 1:
        rand_shape = new ShapeJ(type);
        break;
    case 2:
        rand_shape = new ShapeL(type);
        break;
    case 3:
        rand_shape = new ShapeO(type);
        break;
    case 4:
        rand_shape = new ShapeS(type);
        break;
    case 5:
        rand_shape = new ShapeT(type);
        break;
    case 6:
        rand_shape = new ShapeZ(type);
        break;
    default:
        ERRORLOG("nextShape||unknown shape index||rand_index={}", rand_index);
        break;
    }
    return rand_shape;
}


tile_sprites PlayGameManage::nextTileSprite()
{
    int rand_index = m_last_tile_sprite_index;
    do
    {
        rand_index = getRandomNum(0, 6);
        DEBUGLOG("nextTileSprite||rand_index={}", rand_index);
    } while (rand_index == m_last_tile_sprite_index);
    m_last_tile_sprite_index = rand_index;
    tile_sprites rand_tile_sprite = TILE_DEFAULT;
    switch (rand_index)
    {
    case 0:
        rand_tile_sprite = TILE_BLUE;
        break;
    case 1:
        rand_tile_sprite = TILE_GREEN;
        break;
    case 2:
        rand_tile_sprite = TILE_ORANGE;
        break;
    case 3:
        rand_tile_sprite = TILE_PURPLE;
        break;
    case 4:
        rand_tile_sprite = TILE_RED;
        break;
    case 5:
        rand_tile_sprite = TILE_SKYBLUE;
        break;
    case 6:
        rand_tile_sprite = TILE_YELLOW;
        break;
    default:
        ERRORLOG("nextTileSprite||unknown tile_sprite index||rand_index={}", rand_index);
        break;
    }
    return rand_tile_sprite;
}

void PlayGameManage::updateEliminate(const int& row)
{
    std::set<int> row_set;
    for (std::vector<Tile*>::iterator it=m_tile_vector.begin(); it < m_tile_vector.end(); it++) 
    {
        if ((*it)->getTileRow() == row)
        {
            row_set.insert((*it)->getTileCol());
        }
    }
    if (row_set.size() == m_tile_board_col_nums)
    {
        INFOLOG("updateEliminate||row={}||row_set.size()={}", row, row_set.size());
        // 可以删除该行tile
        for (std::vector<Tile*>::iterator it=m_tile_vector.begin(); it < m_tile_vector.end();) 
        {
            // DEBUGLOG("updateEliminate||row={}||tile_row={}", row, (*it)->getTileRow());
            if ((*it)->getTileRow() == row)
            {
                DEBUGLOG("updateEliminate||col={}", (*it)->getTileCol());
                m_tile_vector.erase(it);
            }
            else if ((*it)->getTileRow() < row)
            {
                (*it)->tileDown(g_tile_length);
                (*it)->updateTileRowCol();
                DEBUGLOG("updateEliminate||row={}||tile_row={}", row, (*it)->getTileRow());
                it++;
            }
            else
            {
                it++;
            }
        }
    }
    else
    {
        DEBUGLOG("updateEliminate||row={}||row_set.size()={}", row, row_set.size());
    }
}


int PlayGameManage::distanceCanShapeDown(const ShapeBase& shape)
{
    short distance = 0;
    ShapeBase temp_shape = shape;
    while (isCanDown(temp_shape))
    {
        temp_shape.shapeDown(1);
        distance++;
        // DEBUGLOG("distanceCanShapeDown||distance={}", distance);
    }
    INFOLOG("distanceCanShapeDown||distance={}", distance);
    return distance;
}