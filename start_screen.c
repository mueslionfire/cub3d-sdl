//
// start_screen.c
//

#include <SDL2/SDL.h>
#include "cub3d.h"

void	render_start_screen(t_data *data)
{
	uint32_t	*pixels;
	SDL_Surface	*surface;
	t_vec_i		window;
	t_vec_i		tx;

	if (data->start.start_flag != 1)
		return ;
	surface = data->surfaces.start_screen;
	pixels = (uint32_t *)surface->pixels;
	window.y = (SCREEN_HEIGHT / 2) - (surface->h / 2);
	for (tx.y = 0; window.y < (SCREEN_HEIGHT / 2) + (surface->h / 2); tx.y++, window.y++)
	{
		window.x = (SCREEN_WIDTH / 2) - (surface->w / 2);
		for (tx.x = 0; window.x < (SCREEN_WIDTH / 2) + (surface->w / 2); tx.x++, window.x++)
		{
			if (pixels[tx.y * surface->w + tx.x] != 0xFFFF0000)
				cub3d_pixel_put(data, window.x, window.y, pixels[tx.y * surface->w + tx.x]);
		}
	}

	// SDL_Rect stretchRect;
	// stretchRect.x = 0;
	// stretchRect.y = 0;
	// stretchRect.w = SCREEN_WIDTH;
	// stretchRect.h = SCREEN_HEIGHT;
	// SDL_BlitSurface(!!!!!, nullptr, data->surfaces.start_screen, &stretchRect);
}
