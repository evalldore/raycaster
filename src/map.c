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

static void Draw_Map(float x, float y, float a)
{
	uint32_t	coordX, coordY;

	Renderer_SetColor(0.4f, 0.4f, 1.0f);
	Renderer_DrawRect(0, 0, WIDTH, HEIGHT >> 1);
	Renderer_SetColor(0.2f, 0.2f, 0.2f);
	Renderer_DrawRect(0, HEIGHT >> 1, WIDTH, HEIGHT);

	for (coordY = 0; coordY < map_h; coordY++)
	{
		for (coordX = 0; coordX < map_h; coordX++)
		{
			if (map[coordY][coordX] == 1)
				Renderer_SetColor(0.0f, 0.0f, 0.0f);
			else
				Renderer_SetColor(1.0f, 1.0f, 1.0f);
			Renderer_DrawRect(coordX * TILE_SIZE + 1, coordY * TILE_SIZE + 1, TILE_SIZE - 2, TILE_SIZE - 2);
		}
	}

	Renderer_SetColor(1.0f, 0.0f, 0.0f);
	glPointSize(10);
	Renderer_DrawPoint(x * TILE_SIZE, y * TILE_SIZE);
	//direction
	Renderer_SetColor(0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	Renderer_DrawLine(x * TILE_SIZE, y * TILE_SIZE, (x * TILE_SIZE) + cos(a) * 25, (y * TILE_SIZE) + sin(a) * 25);
}

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


/*void Map_Draw(float x, float y, float a)
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
		Renderer_DrawLine(4 + r * 8, lineO, 4 + r * 8, lineH + lineO);
		ra = rotate(ra, DR);
	}
}*/

void Map_Draw(float x, float y, float a)
{
	float ra;
	int r;

	//Draw_Map(x, y, a);

	Draw_Ceiling();
	Draw_Floor();
	ra = a - (DR * 30);
	for(r = 0; r < 60; r++)
	{
		fvec_t rayDir = {cos(ra), sin(ra)};
		ivec_t mapCheck = {(int)x, (int)y};
		fvec_t rayStep = {
			(rayDir.x == 0) ? INFINITY : fabs(1.0f / rayDir.x),
			(rayDir.y == 0) ? INFINITY : fabs(1.0f / rayDir.y),
		};
		fvec_t vRayLength1D = {
			(((float)mapCheck.x + 1) - x) * rayStep.x,
			(((float)mapCheck.y + 1) - y) * rayStep.y
		};
		ivec_t vStep = {1, 1};
		if (rayDir.x < 0) 
		{
			vStep.x = -1;
			vRayLength1D.x = (x - (float)mapCheck.x) * rayStep.x;
		}
		if (rayDir.y < 0) 
		{
			vStep.y = -1;
			vRayLength1D.y = (y - (float)mapCheck.y) * rayStep.y;
		}
		bool bTileFound = false;
		float fDistance = 0.0f;
		int	dof = 0;
		while (!bTileFound && dof <= 10)
		{
			if (vRayLength1D.x < vRayLength1D.y) 
			{
				mapCheck.x += vStep.x;
				fDistance = vRayLength1D.x;
				vRayLength1D.x += rayStep.x;
				Renderer_SetColor(1.0f, 0.0f, 0.0f);
			} 
			else 
			{
				mapCheck.y += vStep.y;
				fDistance = vRayLength1D.y;
				vRayLength1D.y += rayStep.y;
				Renderer_SetColor(0.7f, 0.0f, 0.0f);
			}
			if (mapCheck.x >= 0 && mapCheck.x < map_w && mapCheck.y >= 0 && mapCheck.y < map_h)
				bTileFound = map[mapCheck.y][mapCheck.x] == 1;
			dof++;
		}
		if (bTileFound)
		{
			float ca = rotate(a, -ra);
			fDistance *= cos(ca);
			float lineH = fmin((TILE_SIZE * HEIGHT) / (fDistance * TILE_SIZE), HEIGHT);
			float lineO = (HEIGHT >> 1) - lineH / 2;
			glLineWidth(8);
			Renderer_DrawLine(4 + r * 8, lineO, 4 + r * 8, lineH + lineO);
		}
		ra = rotate(ra, DR);
	}
}

/*void Map_Draw(float x, float y, float a)
{
	int	r;
	float ra;
	int	mapX, mapY;
	float sideDistX, sideDistY;
	float deltaDistX, deltaDistY;
	int stepX, stepY;
	bool hit, isHoriz;
	float dirX, dirY;
	int dof;

	Draw_Map(x, y, a);
	ra = a; //rotate(a, DR * -30);
	for (r = 0; r < 1; r++)
	{
		dirX = cos(ra);
		dirY = sin(ra);
		mapX = (int)x >> 6;
		mapY = (int)y >> 6;
		deltaDistX = (dirX == 0) ? INFINITY : abs(1.0f / dirX);
		deltaDistY = (dirY == 0) ? INFINITY : abs(1.0f / dirY);
		sideDistX = (((mapX + 1) * TILE_SIZE) - x) * deltaDistX;
		sideDistY = (((mapY + 1) * TILE_SIZE) - y) * deltaDistY;
		stepX = 1;
		stepY = 1;
		if (dirX < 0)
		{
			stepX = -1;
			sideDistX = (x - (mapX * TILE_SIZE)) * deltaDistX;
		}
		if (dirY < 0)
		{
			stepY = -1;
			sideDistY = (y - (mapY * TILE_SIZE)) * deltaDistY;
		}
		hit = false;
		isHoriz = false;
		dof = 0;
		while (!hit && dof <= 8)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += (deltaDistX * TILE_SIZE);
				mapX += stepX;
				isHoriz = true;
			}
			else
			{
				sideDistY += (deltaDistY * TILE_SIZE);
				mapY += stepY;
				isHoriz = false;
			}
			if ((mapX < 0 || mapX >= map_w) || (mapY < 0 || mapY >= map_h))
				break;
				hit = (map[mapY][mapX] == 1);
			dof++;
		}
		if (hit)
		{
			float perpWallDist;
			if(isHoriz) 
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			float lineH = fmin((TILE_SIZE * HEIGHT) / perpWallDist, HEIGHT);
			float lineO = (HEIGHT >> 1) - lineH / 2;
			//glLineWidth(8);
			//Renderer_SetColor(1.0f, 0.0f, 0.0f);
			//Renderer_DrawLine(512 + r * 8, lineO, 512 + r * 8, lineH + lineO);
			//glLineWidth(1);
			Renderer_SetColor(1.0f, 0.0f, 0.0f);
			Renderer_DrawRect(mapX * TILE_SIZE, mapY * TILE_SIZE, TILE_SIZE, TILE_SIZE);
			//Renderer_DrawLine(x, y, x + dirX * 250, y + dirY * 250);
		}
		ra = rotate(ra, DR);
	}
}*/