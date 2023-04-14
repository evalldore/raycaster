#ifndef ASSETS_H
# define ASSETS_H
# include <SDL2/SDL.h>
# include "utils.h"
# include "glad/glad.h"

enum e_assets {
	ASSET_NONE,
	ASSET_WALLS,
	MAX_ASSETS
};

typedef struct 
{
	uint32_t	glID;
	SDL_Surface *surface;
}	texture_t;

void		Assets_Load(int32_t index, const char *path);
texture_t	*Assets_Get(int32_t index);

#endif