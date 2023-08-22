#include "assets.h"

static texture_t g_tex[MAX_ASSETS];

void Assets_Load(int32_t index, const char *path)
{	
	if (index >= MAX_ASSETS)
		return;

	SDL_Surface *img = SDL_LoadBMP(path);

	if (!img) 
	{
		perror(SDL_GetError());
		return;
	}

	SDL_Surface *converted = SDL_CreateRGBSurfaceWithFormat(0, img->w, img->h, 32, SDL_PIXELFORMAT_RGBA32);
	if (!converted) {
		perror(SDL_GetError());
		SDL_FreeSurface(img);
		return;
	}

	SDL_BlitSurface(img, NULL, converted, NULL);
	SDL_FreeSurface(img);

	uint32_t	glID;
	glGenTextures(1, &glID);
	glBindTexture(GL_TEXTURE_2D, glID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, converted->w, converted->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, converted->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	g_tex[index].surface = converted;
	g_tex[index].glID = glID;
}

texture_t *Assets_Get(int32_t index)
{
	return (&g_tex[index]);
}