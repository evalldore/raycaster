#ifndef GAME_H
# define GAME_H
# include <stdbool.h>
# include "renderer.h"
# include "utils.h"
# include "map.h"
# include "assets.h"
# include "entities.h"
# include "sprites.h"
# include "camera.h"
# define SPEED 5
# define TURN_SPEED 5

typedef struct 
{
	bool up;
	bool down;
	bool left;
	bool right;
}	control_t;

typedef struct
{
	fvec_t	pos;
	float	angle;
}	player_t;

void	Game_Init();
void	Game_Update(double dt);
void	Game_KeyPressed(SDL_KeyboardEvent key);
void	Game_KeyReleased(SDL_KeyboardEvent key);
void	Game_Draw();
void	Game_Exit();

#endif