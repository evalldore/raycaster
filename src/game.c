#include "game.h"
#define PI 3.14159265359
#define P2 PI/2
#define P3 PI*3/2
#define DR 0.0174533

static player_t		ply;
static control_t	controls;
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

int		Game_Init()
{
	ply.pos.x = 256.0f;
	ply.pos.y = 256.0f;
	ply.angle = 0.0f;
}

void	Game_KeyPressed(SDL_KeyboardEvent key)
{
	if (key.keysym.sym == SDLK_w)
		controls.up = true;
	if (key.keysym.sym == SDLK_s)
		controls.down = true;
	if (key.keysym.sym == SDLK_a)
		controls.left = true;
	if (key.keysym.sym == SDLK_d)
		controls.right = true;
}

void	Game_KeyReleased(SDL_KeyboardEvent key)
{
	if (key.keysym.sym == SDLK_w)
		controls.up = false;
	if (key.keysym.sym == SDLK_s)
		controls.down = false;
	if (key.keysym.sym == SDLK_a)
		controls.left = false;
	if (key.keysym.sym == SDLK_d)
		controls.right = false;
}

void	Game_Update(double dt)
{
	if (controls.right)
	{
		ply.angle += TURN_SPEED * dt;
		if (ply.angle > (2 * PI))
			ply.angle -= 2 * PI;
	}
	if (controls.left)
	{
		ply.angle -= TURN_SPEED * dt;
		if (ply.angle < 0.0f)
			ply.angle += 2 * PI;
	}	
	if (controls.up)
	{
		ply.pos.x += cos(ply.angle) * SPEED * dt;
		ply.pos.y += sin(ply.angle) * SPEED * dt;
	}
	if (controls.down)
	{
		ply.pos.x -= cos(ply.angle) * SPEED * dt;
		ply.pos.y -= sin(ply.angle) * SPEED * dt;
	}
}

static void Draw_Player()
{	
	//position
	Renderer_SetColor(1.0f, 0.0f, 0.0f);
	glPointSize(10);
	Renderer_DrawPoint(ply.pos.x, ply.pos.y);
	//direction
	Renderer_SetColor(0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	Renderer_DrawLine(ply.pos.x, ply.pos.y, ply.pos.x + cos(ply.angle) * 25, ply.pos.y + sin(ply.angle) * 25);
}

static float dist(float x1, float y1, float x2, float y2, float ang)
{
	float dist_x = (x2 - x1);
	float dist_y = (y2 - y1);
	return (sqrt((dist_x * dist_x) + (dist_y * dist_y)));
}

static void Draw_Rays()
{
	int r, mx, my, dof;
	float rx, ry, ra, xo, yo, rd;
	ra = ply.angle - DR * 30;
	if (ra < 0.0f)
		ra += 2 * PI;
	else if (ra > 2 * PI)
		ra -= 2 * PI;
	for(r = 0; r < 60; r++)
	{
		//check horizontal line
		dof = 0;
		float dist_h = INFINITY, x_h = ply.pos.x, y_h = ply.pos.y;
		float aTan = -1.0f / tan(ra);
		if (ra > PI)
		{
			ry = (((int)ply.pos.y >> 6) << 6) - 0.0001;
			rx = (ply.pos.y - ry) * aTan + ply.pos.x;
			yo = -TILE_SIZE;
			xo = -yo * aTan;
		}
		else if (ra < PI)
		{
			ry = (((int)ply.pos.y >> 6) << 6) + TILE_SIZE;
			rx = (ply.pos.y - ry) * aTan + ply.pos.x;
			yo = TILE_SIZE;
			xo = -yo * aTan;
		}
		else if (ra == 0.0f || ra == PI)
		{
			rx = ply.pos.x;
			ry = ply.pos.y;
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
				dist_h = dist(ply.pos.x, ply.pos.y, rx, ry, ra);
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		dof = 0;
		float dist_v = INFINITY, x_v = ply.pos.x, y_v = ply.pos.y;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3)
		{
			rx = (((int)ply.pos.x >> 6) << 6) - 0.0001;
			ry = (ply.pos.x - rx) * nTan + ply.pos.y;
			xo = -TILE_SIZE;
			yo = -xo * nTan;
		}
		else if (ra < P2 || ra > P3)
		{
			rx = (((int)ply.pos.x >> 6) << 6) + TILE_SIZE;
			ry = (ply.pos.x - rx) * nTan + ply.pos.y;
			xo = TILE_SIZE;
			yo = -xo * nTan;
		}
		else if (ra == 0.0f || ra == PI)
		{
			rx = ply.pos.x;
			ry = ply.pos.y;
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
				dist_v = dist(ply.pos.x, ply.pos.y, rx, ry, ra);
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
			Renderer_SetColor(0.8f, 0.f, 0.f);
		}
		glLineWidth(3);
		Renderer_DrawLine(ply.pos.x, ply.pos.y, rx, ry);
		float ca = ply.angle - ra;
		if (ca < 0.0f)
			ca += 2 * PI;
		else if (ca > 2 * PI)
			ca -= 2 * PI;

		rd *= cos(ca);

		float lineH = (TILE_SIZE * 320) / rd;
		float lineO = 160 - lineH / 2;
		if (lineH > 320.0f)
			lineH = 320.0f;
		glLineWidth(8);
		Renderer_DrawLine(r * 8 + 530, lineO, r * 8 + 530, lineH + lineO);
		ra += DR;
		if (ra < 0.0f)
			ra += 2 * PI;
		else if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}

static void Draw_Map()
{
	uint32_t	x, y;
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
}

void	Game_Draw()
{
	//Renderer_SetColor(1.0f, 0.0f, 0.0f);
	//Renderer_DrawLine(0.0f, 0.0f, 1024.0f, 512.0f);
	Draw_Map();
	Draw_Rays();
	Draw_Player();
}

void	Game_Exit()
{

}