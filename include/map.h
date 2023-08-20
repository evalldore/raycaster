#ifndef MAP_H
# define MAP_H
# include "utils.h"
# include "assets.h"
# define TILE_SIZE 64
# define LINE_ATTR 16

void		Map_Draw(float x, float y, float a);
int			Map_GetTile(int x, int y);
uint32_t	Map_GetQuality();
void		Map_SetQuality(uint32_t width);
void 		Map_Init();

#endif