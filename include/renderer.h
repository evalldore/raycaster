#ifndef RENDERER_H
# define RENDERER_H
# include <stdbool.h>
# include <SDL2/SDL.h>
# include <glad/glad.h>
# include <fcntl.h>
# include <libft.h>
# define WIDTH 1920
# define HEIGHT 1080

const char* GLErrorString(GLenum error);
void		GLClearAllErrors();
bool		GLCheckErrorStatus(const char *function, int line);

#define GLCheck(x) GLClearAllErrors(); x; GLCheckErrorStatus(#x, __LINE__);

void	Renderer_Init(SDL_Window *window);
void	Renderer_PreDraw();
void	Renderer_PostDraw();
void	Renderer_DrawLine(float sx, float sy, float ex, float ey);
void	Renderer_DrawPoint(float x, float y);
void	Renderer_DrawRect(float x, float y, float w, float h);
void	Renderer_SetColor(float r, float g, float b);
void	Renderer_Clear();
GLuint	Renderer_CreateShader(const char *vertPath, const char *fragPath);
void	Renderer_DrawImage(uint32_t glID, float x, float y, float z, float w, float h);

#endif