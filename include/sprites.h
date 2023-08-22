#ifndef SPRITES_H
#define SPRITES_H
#include "camera.h"
#define MAX_SPRITES 10240

typedef struct
{
	fvec_t		pos;
	int32_t		asset;
	float		scale;
}	sprite_t;

void	Sprites_Draw(camera_t cam);
int32_t	Sprites_Add(fvec_t pos, float scale, int32_t asset);
#endif