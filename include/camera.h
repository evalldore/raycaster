#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"
# include "renderer.h"

typedef struct 
{
	float	fov;
	fvec_t	pos;
	float	angle;
}	camera_t;

void		camera_init(fvec_t pos, float a, float fov);
void		camera_setPos(fvec_t pos);
void		camera_setFOV(float fov);
void		camera_setAngle(float a);
camera_t	camera_get();

#endif