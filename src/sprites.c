#include "renderer.h"
#include "sprites.h"
#include "vector.h"
#include "utils.h"
#include "assets.h"

static uint32_t g_num;
static sprite_t g_data[MAX_SPRITES];

int32_t	Sprites_Add(fvec_t pos, float scale, int32_t asset)
{
	if (g_num >= MAX_SPRITES || asset >= MAX_ASSETS) return (-1);
	g_data[g_num].pos = pos;
	g_data[g_num].scale = scale;
	g_data[g_num].asset = asset;
	return (g_num++);
}

void	Sprites_Draw(camera_t cam)
{
	uint32_t	index;
	for (index = 0; index < g_num; index++)
	{
		fvec_t pos = g_data[index].pos;
		int32_t asset_index = g_data[index].asset;
		float scale = g_data[index].scale;
		texture_t *asset = Assets_Get(asset_index);
		if (!asset) continue;;
		fvec_t angleDir = {cos(cam.angle), sin(cam.angle)};
		float planeAngle = rotate(cam.angle, degToRad(90.f));
		fvec_t planeDir = {cos(planeAngle), sin(planeAngle)};
		fvec_t dist = {pos.x - cam.pos.x, pos.y - cam.pos.y};

		float invDet = 1.0f / (planeDir.x * angleDir.y - angleDir.x * planeDir.y);
		float transformX = invDet * (angleDir.y * dist.x - angleDir.x * dist.y);
		float transformY = invDet * (-planeDir.y * dist.x + planeDir.x * dist.y); //this is actually the depth inside the screen, that what Z is in 3D
		if (transformY < 0.0f) continue;
		float spriteScreenX = (float)(WIDTH >> 1) * (1.0f + transformX / transformY);
		float spriteHeight = (float)fabs((float)HEIGHT / transformY); 
		float drawStartY = spriteHeight / 2.0f + (float)(HEIGHT >> 1);
		float drawEndY = -spriteHeight / 2.0f + (float)(HEIGHT >> 1);
		float size = (float)fabs(drawEndY - drawStartY) * scale;

		Renderer_SetColor(1.0f - (transformY / 11.0f), 1.0f - (transformY / 11.0f), 1.0f - (transformY / 11.0f));
		Renderer_DrawImage(asset->glID, spriteScreenX - (size / 2.0f), drawStartY - size, transformY, size, size);
	}
	g_num = 0;
}