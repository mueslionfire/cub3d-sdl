//
// run.c
//

#include <stdio.h>
#include <string.h>
#include "cub3d.h"

static int	load_new_map(t_data *data);
static void	change_sprite_frames(t_data *data, int x, int y);
static void	update_sprites(t_data *data);
static void	update_fps(t_data *data);
static void	render_time(t_data *data);
static void	finish_game(t_data *data);

void	run(t_data *data)
{
	if (data->new_level == 1)
	{
		if (load_new_map(data) == 1)
		{
			end_loop(data);
			return ;
		}
	}
	if (data->exit == 1)
		finish_game(data);
	else if (data->exit == 0)
	{
		ft_bzero64(data->pixels, SCREEN_WIDTH * SCREEN_HEIGHT
			* sizeof(uint32_t));
		raycast(data);
		update_fps(data);
		update_sprites(data);
		render_time(data);
	}
}

static int	load_new_map(t_data *data)
{
	free_map(data);
	data->pos.x = 0;
	data->pos.y = 0;
	data->current_time = 0;
	data->initial_time = get_time();
	data->map.flr.r = -1;
	data->map.flr.g = -1;
	data->map.flr.b = -1;
	data->map.ceiling.r = -1;
	data->map.ceiling.g = -1;
	data->map.ceiling.b = -1;
	if (strcmp(data->level, LEVEL_1) == 0)
		data->level = LEVEL_2;
	else
		data->level = LEVEL_3;
	if (read_config_file(data, data->level) != 0 || load_textures(data) != 0)
	{
		printf("Error! - loading new map!\n");
		return (1);
	}
	data->new_level = 0;
	return (0);
}

static void	change_sprite_frames(t_data *data, int x, int y)
{
	if (data->current_time - data->map.info[y][x].sprite_time > 100)
	{
		if (data->map.info[y][x].frame_num == 4)
			data->map.info[y][x].frame_num = 0;
		else
			data->map.info[y][x].frame_num++;
		data->map.info[y][x].sprite_time = get_time();
	}
}

static void	update_sprites(t_data *data)
{
	int				x;
	int				y;

	y = 0;
	if (get_time() - data->start.start_time > 3000)
		data->start.start_flag = 0;
	while (data->map.data[y] != NULL)
	{
		x = 0;
		while (data->map.data[y][x] != MAP_END_OF_LINE)
		{
			if (data->map.data[y][x] == MAP_TYPE_WALL_SPRITE
				|| data->map.data[y][x] == MAP_TYPE_PORTAL)
				change_sprite_frames(data, x, y);
			x++;
		}
		y++;
	}
}

static void	update_fps(t_data *data)
{
	data->frames++;
	if (data->current_time - data->initial_time >= 1000)
	{
		printf("%d\n", (data->frames));
		data->frames = 0;
		data->initial_time += 1000;
	}
}

static void	render_time(t_data *data)
{
	char		temp[MAX_NAME_LEN];
	u_int64_t	time;

	time = get_time() - data->start.start_time;
#ifdef __Darwin
	sprintf(temp, "%llu.%llus", time / 1000, time % 1000);
#elif __unix
	sprintf(temp, "%lu.%lus", time / 1000, time % 1000);
#endif // !!!!! #else
}

static void	finish_game(t_data *data)
{
	ft_bzero64(data->pixels, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint32_t));
	// mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
	// server_fetch(data);
	data->exit++;
}
