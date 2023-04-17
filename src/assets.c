#include "assets.h"

static texture_t txt_list[MAX_ASSETS];

void Assets_Load(int32_t index, const char *path)
{	
	uint32_t	glID;
	SDL_Surface *img;
	SDL_Surface *temp;
	SDL_PixelFormat desiredFormat;

	img = SDL_LoadBMP(path);

	if (!img) {
		printf("Failed to load image at %s: %s\n", path, SDL_GetError());
		return;
	}
	
	desiredFormat.format = SDL_PIXELFORMAT_RGBA8888;
	desiredFormat.BitsPerPixel = 32;
    desiredFormat.BytesPerPixel = 4;
    desiredFormat.Rmask = 0x000000ff;
    desiredFormat.Gmask = 0x0000ff00;
    desiredFormat.Bmask = 0x00ff0000;
    desiredFormat.Amask = 0xff000000;

	temp = img;
	img = SDL_ConvertSurface(img, &desiredFormat, 0);
	if (!temp) {
		printf("Failed to convert image at %s: %s\n", path, SDL_GetError());
		return;
	}
	free(temp);

	glGenTextures(1, &glID);
	glBindTexture(GL_TEXTURE_2D, glID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	txt_list[index].surface = img;
	txt_list[index].glID = glID;
}

texture_t *Assets_Get(int32_t index)
{
	return (&txt_list[index]);
}