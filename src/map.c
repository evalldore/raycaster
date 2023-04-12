#include "map.h"
#include "renderer.h"
#include "utils.h"

static uint32_t		map_w = 16, map_h = 16;
static u_int32_t	map[][16] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	
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

void Map_Draw(float x, float y, float a)
{
	float ra;
	int r;
	int	lineWidth = 8;
	int numLines = WIDTH / lineWidth;
	float planeX = 0, planeY = 0.66;

	//Draw_Map(x, y, a);

	Draw_Ceiling();
	Draw_Floor();
	ra = rotate(a, -DR * 30);
	for(r = 0; r < 60; r++)
	{
		float cameraX = 2.0f * r / 60.0f - 1.0f;
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
		while (!bTileFound && dof <= 16)
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
			fDistance *= cos(ra - a);
			float lineH = fmin((TILE_SIZE * HEIGHT) / (fDistance * TILE_SIZE), HEIGHT);
			float lineO = (HEIGHT >> 1) - lineH / 2;
			glLineWidth(8);
			Renderer_DrawLine(240 + 4 + r * 8, lineO, 240 + 4 + r * 8, lineH + lineO);
		}
		ra = rotate(ra, DR);
	}
}
