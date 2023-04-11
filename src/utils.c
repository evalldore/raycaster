#include "utils.h"

float dist(float x1, float y1, float x2, float y2)
{
	float dist_x = (x2 - x1);
	float dist_y = (y2 - y1);
	return (sqrt((dist_x * dist_x) + (dist_y * dist_y)));
}

float rotate(float rad, float dist)
{
	rad = rad + dist;
	if (rad < 0.0f)
		rad += 2 * PI;
	else if (rad > 2 * PI)
		rad -= 2 * PI;
	return (rad);
}