#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"

typedef struct 
{
	float	fov;
	fvec_t	pos;
	float	angle;
}	camera_t;

void camera_init(float x, float y, float a, float fov);
void camera_setPos(float x, float y);
void camera_setFOV(float fov);
void camera_setAngle(float a);
camera_t camera_get();

#endif