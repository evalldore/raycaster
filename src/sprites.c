#include "renderer.h"
#include "sprites.h"
#include "vector.h"
#include "utils.h"

static fvec_t test = {2.0f, 2.0f};

void	Sprites_Draw(float x, float y, float a)
{
	fvec_t angleDir = {cos(a), sin(a)};
	float planeAngle = rotate(a, degToRad(90.f));
	fvec_t planeDir = {cos(planeAngle), sin(planeAngle)};
	fvec_t dist = {test.x - x, test.y - y};

	float invDet = 1.0f / (planeDir.x * angleDir.y - angleDir.x * planeDir.y);
	float transformX = invDet * (angleDir.y * dist.x - angleDir.x * dist.y);
	float transformY = invDet * (-planeDir.y * dist.x + planeDir.x * dist.y); //this is actually the depth inside the screen, that what Z is in 3D
	if (transformY < 0.0f) return;
	float spriteScreenX = (float)(WIDTH >> 1) * (1.0f + transformX / transformY);
	float spriteHeight = abs((float)HEIGHT / transformY); 
    float drawStartY = spriteHeight / 2.0f + (float)HEIGHT / 2.0f;

	Renderer_SetColor(1.0f, 0.0f, 0.0f);
	glPointSize(8.0f);
	Renderer_DrawPoint(spriteScreenX, drawStartY);
	glPointSize(1.0f);
}