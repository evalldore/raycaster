#ifndef GAME_H
# define GAME_H
# include <stdbool.h>
# include <math.h>
# include "vector.h"
# include "renderer.h"
# define SPEED 120
# define TURN_SPEED 5
# define MAP_SIZE 64
# define TILE_SIZE 64
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