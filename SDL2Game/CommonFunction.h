# ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;
static SDL_Renderer* g_menu = NULL;
// Screen
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;



const int RENDER_DRAW_COLOR = 0Xff;

const int FRAME_PER_SECOND = 60;

#define TILE_SIZE 64

#define MAX_MAP_X 400
#define MAX_MAP_Y 10
#define COIN 4

typedef struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
	int jump_;

};


typedef struct Map
{
	int start_x_;
	int start_y_;

	int max_x_;
	int max_y_;

	int tile[MAX_MAP_Y][MAX_MAP_X];
	char* file_name_;
};


#endif