#ifndef GAME_H
# define GAME_H
# include <glad/glad.h>
# include <SDL2/SDL.h>
# include <GL/gl.h>

int		Game_Init();
void	Game_Update(double dt);
void	Game_KeyPressed(SDL_KeyboardEvent key);
void	Game_KeyReleased(SDL_KeyboardEvent key);
void	Game_Draw();
void	Game_Exit();

#endif