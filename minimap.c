//
// minimap.c
//

#include <string.h>
#include "cub3d.h"

static void	update_player_pos(t_data *data, t_vec_i square);
static void	color_rect(t_data *data, t_vec_i pix_pos, int color);
static int	render_rect(t_data *data, t_rect rect);
static t_vec_i	calc_square(t_data *data);
static void	select_square_color(t_data *data, t_vec_i map, t_vec_i pix_pos);
static int	return_color(t_data *data, int flag);

void	render_minimap(t_data *data)
{
	t_vec_i	square;
	t_vec_i	pix_pos;
	t_vec_i	map;

	square = calc_square(data);
	data->minimap.width = square.x * data->map.x;
	data->minimap.height = square.y * data->map.y;
	pix_pos.y = 20;
	map.y = -1;
	while (data->map.data[++map.y] != NULL && data->exit == 0)
	{
		map.x = -1;
		pix_pos.x = 0;
		while (data->map.data[map.y][++map.x] != MAP_END_OF_LINE)
		{
			select_square_color(data, map, pix_pos);
			pix_pos.x += square.x;
		}
		pix_pos.y += square.y;
	}
	update_player_pos(data, square);
}

static void	update_player_pos(t_data *data, t_vec_i square)
{
	t_rect	temp;

	temp.width = square.x / 3;
	temp.height = square.y / 3;
	temp.x0 = square.x * data->pos.x + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = (square.y * data->pos.y) + 20;
	temp.color = 0xFF0000;
	render_rect(data, temp);
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 4)) + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = (square.y * (data->pos.y + (data->dir.y / 4))) + 20;
	render_rect(data, temp);
	temp.x0 = square.x * (data->pos.x + (data->dir.x / 2)) + \
		(SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = (square.y * (data->pos.y + (data->dir.y / 2))) + 20;
	render_rect(data, temp);
}

static void	color_rect(t_data *data, t_vec_i pix_pos, int color)
{
	t_vec_i	square;
	t_rect	temp;

	square = calc_square(data);
	temp.width = square.x;
	temp.height = square.y;
	temp.x0 = pix_pos.x + (SCREEN_WIDTH - data->minimap.width) - 20;
	temp.y0 = pix_pos.y;
	temp.color = color;
	render_rect(data, temp);
}

static int	render_rect(t_data *data, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y0;
	while (i < rect.y0 + rect.height)
	{
		j = rect.x0;
		while (j < rect.x0 + rect.width)
			cub3d_pixel_put(data, j++, i, rect.color);
		++i;
	}
	return (0);
}

static t_vec_i	calc_square(t_data *data)
{
	t_vec_i	square;

	square.x = (SCREEN_WIDTH / 3) / data->map.x;
	square.y = (SCREEN_HEIGHT / 3) / data->map.y;
	if (data->map.x < data->map.y)
		square.y = square.x;
	else
		square.x = square.y;
	return (square);
}

static void	select_square_color(t_data *data, t_vec_i map, t_vec_i pix_pos)
{
	if (data->map.info[map.y][map.x].visible == 1)
	{
		if (data->map.data[map.y][map.x] == MAP_TYPE_EMPTY_SPACE)
			color_rect(data, pix_pos, create_trgb(0, data->map.flr.r, \
				data->map.flr.g, data->map.flr.b));
		if (data->map.data[map.y][map.x] == MAP_TYPE_WALL || \
			data->map.data[map.y][map.x] == MAP_TYPE_WALL_SPRITE)
			color_rect(data, pix_pos, return_color(data, 0));
		if (data->map.data[map.y][map.x] == MAP_TYPE_DOOR)
			color_rect(data, pix_pos, return_color(data, 1));
		if (data->map.data[map.y][map.x] == MAP_TYPE_PORTAL)
			color_rect(data, pix_pos, 0x00FF00);
		if (data->map.data[map.y][map.x] == MAP_TYPE_EXIT)
			color_rect(data, pix_pos, 0x800000);
	}
}

static int	return_color(t_data *data, int flag)
{
	int	wall_color;
	int	door_color;

	wall_color = 0xFFFFFF;
	door_color = 0xCC6600;
	if (strcmp(data->level, LEVEL_3) == 0)
	{
		wall_color = 0x000000;
		door_color = 0x2B1D14;
	}
	if (flag == 1)
		return (door_color);
	return (wall_color);
}
