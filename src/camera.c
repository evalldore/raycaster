#include "camera.h"

static camera_t	g_cam;

void camera_init(fvec_t pos, float a, float fov)
{
	g_cam.pos = pos;
	g_cam.angle = a;
	g_cam.fov = fov;
}

/*fvec_t	camera_toScreen(fvec_t pos)
{
	fvec_t angleDir = {cos(g_cam.angle), sin(g_cam.angle)};
	float planeAngle = rotate(g_cam.angle, degToRad(90.f));
	fvec_t planeDir = {cos(planeAngle), sin(planeAngle)};
	fvec_t dist = {pos.x - g_cam.pos.x, pos.y - g_cam.pos.y};

	float invDet = 1.0f / (planeDir.x * angleDir.y - angleDir.x * planeDir.y);
	float transformX = invDet * (angleDir.y * dist.x - angleDir.x * dist.y);
	float transformY = invDet * (-planeDir.y * dist.x + planeDir.x * dist.y); //this is actually the depth inside the screen, that what Z is in 3D
	if (transformY < 0.0f) return;
	float spriteScreenX = (float)(WIDTH >> 1) * (1.0f + transformX / transformY);
	float spriteHeight = abs((float)HEIGHT / transformY); 
    float drawStartY = spriteHeight / 2.0f + (float)(HEIGHT >> 1);
	float drawEndY = -spriteHeight / 2.0f + (float)(HEIGHT >> 1);
	float size = abs(drawEndY - drawStartY);
}*/

camera_t camera_get()
{
	return (g_cam);
}

void camera_setAngle(float a)
{
	g_cam.angle = a;
}

void camera_setFOV(float fov)
{
	g_cam.fov = fov;
}

void camera_setPos(fvec_t pos)
{
	g_cam.pos = pos;
}