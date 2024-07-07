#include "global.h"

Mix_Music* g_background_music = nullptr;

Mix_Chunk* g_select_button_sound = nullptr;

SDLWindow* g_main_window = nullptr;

TTF_Font* g_normal_font = nullptr;

SDLTexture* g_tile_texture = nullptr;

SDL_Rect g_tile_clips[TOTAL_TILE_SPRITES];

int g_tile_length = -1;

int g_tile_resource_length = -1;

SDL_Rect g_tile_board_region = {-1, -1, -1, -1};

int g_tile_board_middle = -1;

