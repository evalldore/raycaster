#ifndef CAMERA_H
# define CAMERA_H
# include "vector.h"

typedef struct 
{
	float	fov;
	fvec_t	plane;
	float	angle;
}	camera_t;

#endif