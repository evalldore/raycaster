#ifndef RENDERER_H
# define RENDERER_H
# include <stdbool.h>
# include <SDL2/SDL.h>
# include <glad/glad.h>
# include <fcntl.h>
# include <libft.h>
# define WIDTH 1024
# define HEIGHT 512

void	Renderer_Init(SDL_Window *window);
void	Renderer_PreDraw();
void	Renderer_PostDraw();
void	Renderer_DrawLine(float sx, float sy, float ex, float ey);
void	Renderer_DrawPoint(float x, float y);
void	Renderer_DrawRect(float x, float y, float w, float h);
void	Renderer_SetColor(float r, float g, float b);
void	Renderer_Clear();

#endif