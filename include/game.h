#ifndef GAME_H
# define GAME_H
# include "renderer.h"

int		Game_Init();
void	Game_Update(double dt);
void	Game_KeyPressed(SDL_KeyboardEvent key);
void	Game_KeyReleased(SDL_KeyboardEvent key);
void	Game_Draw();
void	Game_Exit();

#endif