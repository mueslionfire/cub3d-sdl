//
// cleanup.c
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "cub3d.h"

static void	cub3d_free_surfaces(t_data *data);
static void	free_map_surfaces(t_data *data);

void	cub3d_cleanup(t_data *data)
{
	if (data == nullptr)
		return ;
	cub3d_free_surfaces(data);
	free_map(data);
	if (data->pixels != nullptr)
		free(data->pixels);
	SDL_DestroyTexture(data->framebuffer);
	SDL_DestroyRenderer(data->renderer);
	SDL_DestroyWindow(data->window);
	IMG_Quit();
	SDL_Quit();
	free(data);
}

static void	cub3d_free_surfaces(t_data *data)
{
	SDL_FreeSurface(data->surfaces.start_screen);
}

void	free_map(t_data *data)
{
	if (data->map.data == NULL)
		return ;
	free_map_surfaces(data);
	if (data->map.tx_no != NULL)
		free(data->map.tx_no);
	if (data->map.tx_ea != NULL)
		free(data->map.tx_ea);
	if (data->map.tx_so != NULL)
		free(data->map.tx_so);
	if (data->map.tx_we != NULL)
		free(data->map.tx_we);
	for (int i = 0; data->map.data[i] != NULL; i++)
	{
		free(data->map.data[i]);
		free(data->map.info[i]);
	}
	free(data->map.data);
	free(data->map.info);
	bzero(&data->map, sizeof(t_map));
}

static void	free_map_surfaces(t_data *data)
{
	SDL_FreeSurface(data->surfaces.tex_north);
	SDL_FreeSurface(data->surfaces.tex_east);
	SDL_FreeSurface(data->surfaces.tex_south);
	SDL_FreeSurface(data->surfaces.tex_west);
	SDL_FreeSurface(data->surfaces.tex_door);
	SDL_FreeSurface(data->surfaces.tex_exit);
	for (int i = 0; i < 5; i++)
	{
		SDL_FreeSurface(data->surfaces.tex_torch[i]);
		SDL_FreeSurface(data->surfaces.tex_portal[i]);
	}
}
