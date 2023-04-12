#ifndef GAME_H
# define GAME_H
# include <stdbool.h>
# include "renderer.h"
# include "utils.h"
# include "map.h"
# define SPEED 2
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

int		Game_Init();
void	Game_Update(double dt);
void	Game_KeyPressed(SDL_KeyboardEvent key);
void	Game_KeyReleased(SDL_KeyboardEvent key);
void	Game_Draw();
void	Game_Exit();

#endif