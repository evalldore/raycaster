#ifndef	UTILS_H
# define UTILS_H
# include <math.h>
# include <stdbool.h>
# include "vector.h"
# define PI 3.14159265359
# define P2 PI/2
# define P3 PI*3/2
# define DR 0.0174533

float dist(float x1, float y1, float x2, float y2);
float rotate(float rad, float dist);

#endif