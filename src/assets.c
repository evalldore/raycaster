#include "assets.h"

static texture_t txt_list[MAX_ASSETS];

void Assets_Load(int32_t index, const char *path)
{	
	uint32_t	glID;
	SDL_Surface *img;

	img = SDL_LoadBMP(path);
	if (!img)
		return;
	glGenTextures(1, &glID);
	glBindTexture(GL_TEXTURE_2D, glID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_BYTE, img->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	txt_list[index].surface = img;
	txt_list[index].glID = glID;
}

texture_t *Assets_Get(int32_t index)
{
	return (&txt_list[index]);
}