#pragma once

#include "SDL2/SDL.h"

// 单人游戏玩家输
#define PLAYER_LOSE_EVENT				(SDL_USEREVENT+1)
// 开始游戏，进入选择游戏方式界面
#define START_GAME_EVENT				(SDL_USEREVENT+2)
// 查看最好分数
#define BEST_SCORES_EVENT				(SDL_USEREVENT+3)
// 退出游戏
#define EXIT_GAME_EVENT	    			(SDL_USEREVENT+4)
// 单人游戏
#define SINGLE_PLAYER_EVENT	    		(SDL_USEREVENT+5)
// 返回主菜单
#define BACK_MANU_EVENT	    			(SDL_USEREVENT+6)
// 单人游戏再来一局
#define SINGLE_PLAYER_AGAIN_GAME_EVENT	(SDL_USEREVENT+7)


// 枚举元素的组成类型
typedef enum {
	TILE_BLUE, 
	TILE_GREEN,
	TILE_ORANGE,
	TILE_PURPLE,
	TILE_RED,
	TILE_SKYBLUE,
	TILE_YELLOW,
	TILE_DEFAULT    // 默认，黑色
} tile_sprites;

// 定义tile的种类  
const int TOTAL_TILE_SPRITES = 8;

// 枚举渲染的种类
typedef enum {
	DEFAULT_INTERFACE,
	MAIN_MENU_INTERFACE,          // 选择开始游戏和退出游戏
	PLAY_GAME_INTERFACE,           // 对战中
	PLAYER_LOSE_INTERFACE,        // 单人游戏输了，选择再来一局或者退出游戏
	PLAYER_LOSE_PRE_INTERFACE,    // 单人游戏输了前一帧，为了确保能将电脑最后一步下的棋渲染出来
	BEST_SCORE_INTERFACE          // 输出排行榜分数
} interface_kind_type;

typedef enum {
    BUTTON_SPRITE_MOUSE_OUT,            // 鼠标不在按键上，一般用于默认值
    BUTTON_SPRITE_MOUSE_OVER_MOTION,	// 鼠标在按键上
    BUTTON_SPRITE_MOUSE_DOWN,			// 鼠标在按键上，且按下
    BUTTON_SPRITE_MOUSE_UP,				// 鼠标在按键上，释放按键
    BUTTON_SPRITE_TOTAL
} sdl_button_sprite;

// tile_board的信息，包含左上角的坐标，横/纵向tile数量
struct TileBoardInfo {
	int top_left_x;
	int top_left_y;
	int row_tiles;
	int col_tiles;
};


