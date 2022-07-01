//
// sdl_utils.c
//

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "cub3d.h"

SDL_Surface *load_surface(const char *path)
{
	SDL_PixelFormat	*format;
	SDL_Surface 	*optimized;
	SDL_Surface 	*temp;

	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
	if (format == NULL)
	{
		// TODO !!!!!
		return (NULL);
	}
	temp = IMG_Load(path);
	if (temp == NULL)
	{
		// TODO !!!!!
		return (NULL);
	}
	optimized = SDL_ConvertSurface(temp, format, 0);
	SDL_FreeSurface(temp);
	if (optimized == NULL)
	{
		// !!!!!
		return (NULL);
	}
	SDL_FreeFormat(format);
	return (optimized);
}
