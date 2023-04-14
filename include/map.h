#ifndef MAP_H
# define MAP_H
# include "utils.h"
# define TILE_SIZE 64

void	Map_Draw(float x, float y, float a);
int		Map_GetTile(int x, int y);
void 	Map_Init();

#endif