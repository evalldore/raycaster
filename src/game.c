#include "game.h"

static player_t		ply;
static control_t	controls;

void	Game_Init()
{
	Assets_Load(ASSET_WALLS, "./assets/textures/wolftextures.bmp");
	Assets_Load(ASSET_SPRITE, "./assets/textures/sprite.bmp");
	ents_register();
	Map_Init();
	//fvec_t	pos = {2.0f, 2.0f};
	//ents_sprite(pos);
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

	if (key.keysym.sym == SDLK_KP_PLUS)
		Map_SetQuality(Map_GetQuality() + 1);
	if (key.keysym.sym == SDLK_KP_MINUS)
		Map_SetQuality(Map_GetQuality() - 1);
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

void	Game_Draw()
{
	Map_Draw(ply.pos.x, ply.pos.y, ply.angle);
	Sprites_Draw(ply.pos.x, ply.pos.y, ply.angle);
}

void	Game_Exit()
{

}