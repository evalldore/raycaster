#include "renderer.h"
#include "sprites.h"
#include "vector.h"
#include "utils.h"

static fvec_t test = {2.0f, 2.0f};

void	Sprites_Draw(camera_t cam)
{
	fvec_t angleDir = {cos(cam.angle), sin(cam.angle)};
	float planeAngle = rotate(cam.angle, degToRad(90.f));
	fvec_t planeDir = {cos(planeAngle), sin(planeAngle)};
	fvec_t dist = {test.x - cam.pos.x, test.y - cam.pos.y};

	float invDet = 1.0f / (planeDir.x * angleDir.y - angleDir.x * planeDir.y);
	float transformX = invDet * (angleDir.y * dist.x - angleDir.x * dist.y);
	float transformY = invDet * (-planeDir.y * dist.x + planeDir.x * dist.y); //this is actually the depth inside the screen, that what Z is in 3D
	if (transformY < 0.0f) return;
	float spriteScreenX = (float)(WIDTH >> 1) * (1.0f + transformX / transformY);
	float spriteHeight = (float)fabs((float)HEIGHT / transformY); 
    float drawStartY = spriteHeight / 2.0f + (float)(HEIGHT >> 1);
	float drawEndY = -spriteHeight / 2.0f + (float)(HEIGHT >> 1);
	float size = (float)fabs(drawEndY - drawStartY) * 0.8f;

	texture_t *asset = Assets_Get(ASSET_SPRITE);
	Renderer_SetColor(1.0f, 1.0f, 1.0f);
	Renderer_DrawImage(asset->glID, spriteScreenX - (size / 2.0f), drawStartY - size, transformY, size, size);
}