//
// config_check.c
//

#include "cub3d.h"

static int	check_for_walls(int **map, int x, int y);
static int	check_map(t_data *data, int **map, t_vec *pos);
static int	process_starting_position(t_data *data, int x, int y, t_vec *pos);
static void	set_orientation(t_data *data, int type);
static int	get_map_width(int *line);

int	check_input(t_data *data)
{
	if (data->map.tx_no == NULL || data->map.tx_ea == NULL
		|| data->map.tx_so == NULL || data->map.tx_we == NULL)
		return (-1);
	if (data->map.flr.r == -1 || data->map.flr.g == -1
		|| data->map.flr.b == -1)
		return (-1);
	if (data->map.ceiling.r == -1 || data->map.ceiling.g == -1
		|| data->map.ceiling.b == -1)
		return (-1);
	if (data->map.x == 0 || data->map.y == 0)
		return (-1);
	if (check_map(data, data->map.data, &data->pos) != 0)
		return (-1);
	if (data->pos.x == 0 || data->pos.y == 0)
		return (-1);
	return (0);
}

static int	check_map(t_data *data, int **map, t_vec *pos)
{
	int			x;
	int			y;

	y = -1;
	while (map[++y] != NULL)
	{
		x = -1;
		while (map[y][++x] != MAP_END_OF_LINE)
		{
			if (map[y][x] == MAP_TYPE_UNKNOWN)
				return (-1);
			if (map[y][x] == MAP_TYPE_N || map[y][x] == MAP_TYPE_E
				|| map[y][x] == MAP_TYPE_S || map[y][x] == MAP_TYPE_W)
			{
				if (process_starting_position(data, x, y, pos) != 0)
					return (-1);
			}
			else if (map[y][x] == MAP_TYPE_WALL_SPRITE)
				data->map.info[y][x].frame_num = (y + x) % 4;
			if (check_for_walls(map, x, y) != 0)
				return (-1);
		}
	}
	return (0);
}

static int	process_starting_position(t_data *data, int x, int y, t_vec *pos)
{
	if (pos->x != 0 || pos->y != 0)
		return (-1);
	pos->x = x + 0.5;
	pos->y = y + 0.5;
	set_orientation(data, data->map.data[y][x]);
	data->map.data[y][x] = MAP_TYPE_EMPTY_SPACE;
	return (0);
}

static int	check_for_walls(int **map, int x, int y)
{
	if (map[y][x] == MAP_TYPE_EMPTY_SPACE || map[y][x] == MAP_TYPE_N
		|| map[y][x] == MAP_TYPE_E || map[y][x] == MAP_TYPE_S
		|| map[y][x] == MAP_TYPE_W || map[y][x] == MAP_TYPE_DOOR)
	{
		if (y == 0 || x == 0)
			return (-1);
		if (map[y][x + 1] == MAP_END_OF_LINE)
			return (-1);
		if (map[y + 1] == NULL)
			return (-1);
		if (map[y][x - 1] == MAP_TYPE_NOTHINGNESS
			|| map[y][x + 1] == MAP_TYPE_NOTHINGNESS
			|| (get_map_width(map[y - 1]) < x
			|| map[y - 1][x] == MAP_TYPE_NOTHINGNESS)
			|| (get_map_width(map[y + 1]) < x
			|| map[y + 1][x] == MAP_TYPE_NOTHINGNESS))
			return (-1);
	}
	return (0);
}

static void	set_orientation(t_data *data, int type)
{
	data->dir.x = 0;
	data->dir.y = 0;
	data->camera_plane.x = 0;
	if (type == MAP_TYPE_N)
	{
		data->dir.y = -1;
		data->camera_plane.x = 1;
		data->camera_plane.y = 0;
	}
	else if (type == MAP_TYPE_E)
	{
		data->dir.x = 1;
		data->camera_plane.y = 1;
	}
	else if (type == MAP_TYPE_S)
	{
		data->dir.y = 1;
		data->camera_plane.x = -1;
		data->camera_plane.y = 0;
	}
	else if (type == MAP_TYPE_W)
	{
		data->dir.x = -1;
		data->camera_plane.y = -1;
	}
}

static int	get_map_width(int *line)
{
	int	i;

	i = 0;
	while (line[i] != MAP_END_OF_LINE)
		i++;
	return (i);
}
