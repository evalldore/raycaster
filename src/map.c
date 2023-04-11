#include "map.h"
#include "renderer.h"
#include "utils.h"

static uint32_t		map_w = 8, map_h = 8;
static u_int32_t	map[][8] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

/*static void Draw_Map()
{
	uint32_t	x, y;

	Renderer_SetColor(0.4f, 0.4f, 1.0f);
	Renderer_DrawRect(0, 0, WIDTH, HEIGHT >> 1);
	Renderer_SetColor(0.2f, 0.2f, 0.2f);
	Renderer_DrawRect(0, HEIGHT >> 1, WIDTH, HEIGHT);

	for (y = 0; y < map_h; y++)
	{
		for (x = 0; x < map_h; x++)
		{
			if (map[y][x] == 1)
				Renderer_SetColor(0.0f, 0.0f, 0.0f);
			else
				Renderer_SetColor(1.0f, 1.0f, 1.0f);
			Renderer_DrawRect(x * TILE_SIZE + 1, y * TILE_SIZE + 1, TILE_SIZE - 2, TILE_SIZE - 2);
		}
	}
}*/

/*static void Draw_Player()
{	
	//position
	Renderer_SetColor(1.0f, 0.0f, 0.0f);
	glPointSize(10);
	Renderer_DrawPoint(ply.pos.x, ply.pos.y);
	//direction
	Renderer_SetColor(0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	Renderer_DrawLine(ply.pos.x, ply.pos.y, ply.pos.x + cos(ply.angle) * 25, ply.pos.y + sin(ply.angle) * 25);
}*/

static void	Draw_Ceiling()
{
	Renderer_SetColor(0.3f, 0.3f, 1.0f);
	Renderer_DrawRect(0.f, 0.f, WIDTH, HEIGHT >> 1);
}

static void	Draw_Floor()
{
	Renderer_SetColor(0.3f, 0.3f, 0.3f);
	Renderer_DrawRect(0.f, HEIGHT >> 1, WIDTH, HEIGHT);
}

void Map_Draw(float x, float y, float a)
{
	int r, mx, my, dof;
	float rx, ry, ra, xo, yo, rd;

	Draw_Ceiling();
	Draw_Floor();
	ra = rotate(a, DR * -30);
	for(r = 0; r < 60; r++)
	{
		dof = 0;
		float dist_h = INFINITY, x_h = x, y_h = y;
		float aTan = -1.0f / tan(ra);
		if (ra > PI)
		{
			ry = (((int)y >> 6) << 6) - 0.0001;
			rx = (y - ry) * aTan + x;
			yo = -TILE_SIZE;
			xo = -yo * aTan;
		}
		else if (ra < PI)
		{
			ry = (((int)y >> 6) << 6) + TILE_SIZE;
			rx = (y - ry) * aTan + x;
			yo = TILE_SIZE;
			xo = -yo * aTan;
		}
		else if (ra == 0.0f || ra == PI)
		{
			rx = x;
			ry = y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if (mx < map_w && my < map_h && map[my][mx] == 1)
			{
				dof = 8;
				x_h = rx;
				y_h = ry;
				dist_h = dist(x, y, rx, ry);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		dof = 0;
		float dist_v = INFINITY, x_v = x, y_v = y;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)x >> 6) << 6) - 0.0001;
			ry = (x - rx) * nTan + y;
			xo = -TILE_SIZE;
			yo = -xo * nTan;
		}
		else if (ra < P2 || ra > P3)
		{
			rx = (((int)x >> 6) << 6) + TILE_SIZE;
			ry = (x - rx) * nTan + y;
			xo = TILE_SIZE;
			yo = -xo * nTan;
		}
		else if (ra == 0.0f || ra == PI)
		{
			rx = x;
			ry = y;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			if (mx < map_w && my < map_h && map[my][mx] == 1)
			{
				dof = 8;
				x_v = rx;
				y_v = ry;
				dist_v = dist(x, y, rx, ry);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (dist_h < dist_v)
		{
			rx = x_h;
			ry = y_h;
			rd = dist_h;
			Renderer_SetColor(1.0f, 0.f, 0.f);
		}
		else if (dist_v < dist_h)
		{
			rx = x_v;
			ry = y_v;
			rd = dist_v;
			Renderer_SetColor(0.7f, 0.f, 0.f);
		}
		float ca = rotate(a, -ra);
		rd *= cos(ca);
		float lineH = fmin((TILE_SIZE * HEIGHT) / rd, HEIGHT);
		float lineO = (HEIGHT >> 1) - lineH / 2;
		glLineWidth(8);
		Renderer_DrawLine(r * 8, lineO, r * 8, lineH + lineO);
		ra = rotate(ra, DR);
	}
}