#ifndef MAP_H
# define MAP_H
# include "utils.h"
# include "assets.h"
# include "camera.h"
# define TILE_SIZE 64
# define LINE_ATTR 16

void		Map_Draw(camera_t cam);
uint32_t	Map_GetTile(uint32_t x, uint32_t y);
uint32_t	Map_GetQuality();
void		Map_SetQuality(uint32_t width);
void 		Map_Init();

#endif