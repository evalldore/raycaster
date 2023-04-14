#include "assets.h"

static SDL_Texture *txt_list[MAX_ASSETS];

static SDL_Texture *loadImage(const char *path)
{
	SDL_Texture *newTexture = NULL;

	SDL_Surface *image = IMG_LoadTexture()
}

void Assets_Load(int32_t index, const char *path)
{
	txt_list[index] = loadImage(path); 
}