#include "game.h"

static player_t		ply;
static control_t	controls;

int		Game_Init()
{
	Assets_Load(ASSET_WALLS, "./assets/textures/wolftextures.bmp");
	printf("%p\n", Assets_Get(ASSET_WALLS));
	Map_Init();
	ply.pos.x = 8.0f;
	ply.pos.y = 8.0f;
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
		ply.angle = rotate(ply.angle, TURN_SPEED * dt);
	if (controls.left)
		ply.angle = rotate(ply.angle, -TURN_SPEED * dt);
	if (controls.up)
	{
		ivec_t forwardCoords = {
			ply.pos.x + cos(ply.angle) * 0.5f,
			ply.pos.y + sin(ply.angle) * 0.5f
		};
		if (Map_GetTile(forwardCoords.x, (int)ply.pos.y) == 0)
			ply.pos.x += cos(ply.angle) * SPEED * dt;
		if (Map_GetTile((int)ply.pos.x, forwardCoords.y) == 0)
			ply.pos.y += sin(ply.angle) * SPEED * dt;
	}
	if (controls.down)
	{
		ivec_t forwardCoords = {
			ply.pos.x - cos(ply.angle) * 0.5f,
			ply.pos.y - sin(ply.angle) * 0.5f
		};
		if (Map_GetTile(forwardCoords.x, (int)ply.pos.y) == 0)
			ply.pos.x -= cos(ply.angle) * SPEED * dt;
		if (Map_GetTile((int)ply.pos.x, forwardCoords.y) == 0)
			ply.pos.y -= sin(ply.angle) * SPEED * dt;

	}
}

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

void	Game_Draw()
{
	Map_Draw(ply.pos.x, ply.pos.y, ply.angle);
}

void	Game_Exit()
{

}