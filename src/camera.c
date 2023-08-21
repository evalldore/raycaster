#include "camera.h"

static camera_t	g_cam;

void camera_init(fvec_t pos, float a, float fov)
{
	g_cam.pos = pos;
	g_cam.angle = a;
	g_cam.fov = fov;
}

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