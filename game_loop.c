//
// game_loop.c
//

#include <SDL2/SDL.h>
#include "cub3d.h"

void	game_loop(t_data *data)
{
	int			quit;
	SDL_Event	event;

	SDL_ShowCursor(0);
	quit = 0;
	while (quit == 0)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = 1;
			else if (event.type == SDL_KEYDOWN)
				key_cb(data, event.key.keysym.sym);
			else if (event.type == SDL_MOUSEMOTION)
				mouse_cb(data);
		}
		run(data);
		render_start_screen(data);
		SDL_UpdateTexture(data->framebuffer, NULL, data->pixels, SCREEN_WIDTH * sizeof(uint32_t));
		SDL_RenderClear(data->renderer);
		SDL_RenderCopy(data->renderer, data->framebuffer, NULL, NULL);
		SDL_RenderPresent(data->renderer);
	}
}
