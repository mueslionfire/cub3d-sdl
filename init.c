//
// init.c
//

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "cub3d.h"

static int	cub3d_sdl_init(t_data *data);
static void	general_init(t_data *data, const char *user_name);

t_data	*cub3d_init(const char *user_name)
{
	t_data	*data;

	data = calloc(1, sizeof(t_data));
	if (data == nullptr)
		return (nullptr);
	if (cub3d_sdl_init(data) != 0)
		return (nullptr);
	// if (data->window != nullptr)
	// 	SDL_DestroyWindow(data->window);
	// free(data);
	general_init(data, user_name);
	return (data);
}

static int	cub3d_sdl_init(t_data *data)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (1);
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) == 0)
		return (1);
	data->window = SDL_CreateWindow("cub3d", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (data->window == nullptr)
		return (1);
	data->renderer = SDL_CreateRenderer(data->window, -1, SDL_RENDERER_ACCELERATED);
	if (data->renderer == NULL)
		return (1);
	SDL_SetRenderDrawColor(data->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	data->framebuffer = SDL_CreateTexture(data->renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (data->framebuffer == NULL)
		return (1);
	data->pixels = malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint32_t));
	if (data->pixels == NULL)
		return (1);
	return (0);
}

static void	general_init(t_data *data, const char *user_name)
{
	if (user_name != NULL)
		strlcpy(data->user_name, user_name, MAX_NAME_LEN);
	data->current_time = 0;
	data->initial_time = get_time();
	data->map.flr.r = -1;
	data->map.flr.g = -1;
	data->map.flr.b = -1;
	data->map.ceiling.r = -1;
	data->map.ceiling.g = -1;
	data->map.ceiling.b = -1;
	data->mouse_pos.x = SCREEN_WIDTH / 2;
	data->mouse_pos.y = SCREEN_HEIGHT / 2;
	data->level = LEVEL_1;
	data->surfaces.start_screen = load_surface("./textures/start_screen.png");
	if (data->surfaces.start_screen == nullptr)
		data->start.start_flag = 0;
	else
		data->start.start_flag = 1;
}
