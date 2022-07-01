//
// input.c
//

#include "cub3d.h"

int	key_cb(t_data *data, int keycode)
{
	// switch (keycode)
	// {
	// 	case SDLK_ESCAPE:
	// 		end_loop(data);
	// 		break;
	// 	// ...
	// 	default:
	// 		break;
	// }
	if (keycode == SDLK_ESCAPE)
		end_loop(data);
	else if (keycode == SDLK_LEFT)
		key_left(data);
	else if (keycode == SDLK_RIGHT)
		key_right(data);
	else if (keycode == SDLK_w)
		key_w(data);
	else if (keycode == SDLK_a)
		key_a(data);
	else if (keycode == SDLK_s)
		key_s(data);
	else if (keycode == SDLK_d)
		key_d(data);
	else if (keycode == SDLK_f)
		key_f(data);
	return (0);
}

// data->rot_speed = 0.05 -> modified for "mouse sensitivity"
int	mouse_cb(t_data *data)
{
	int	x;
	int	y;

	SDL_GetMouseState(&x, &y);
	if (data->exit > 0)
		return (0);
	if (x < data->mouse_pos.x)
	{
		// mlx_mouse_move(data->mlx, data->window, data->mouse_pos.x,
		// 	data->mouse_pos.y);
		data->rot_speed = 0.05;
		key_left(data);
	}
	if (x > data->mouse_pos.x)
	{
		// mlx_mouse_move(data->mlx, data->window, data->mouse_pos.x,
		// 	data->mouse_pos.y);
		data->rot_speed = 0.05;
		key_right(data);
	}
	return (0);
}

int	end_loop(t_data *data)
{
	(void)data; // !!!!!
	SDL_Quit();
	return (0);
}
