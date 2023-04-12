#include "camera.h"

static camera_t	cam;

void camera_init(float a, float fov)
{
	cam.plane.x = 0.0f;
	cam.plane.y = (fov / 180.0f) * 2.0f;
	cam.fov = fov;
}

void camera_get()
{
	return (cam);
}

void camera_setFOV(float fov)
{

}