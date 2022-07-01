//
// config_map.c
//

#include <string.h>
#include "cub3d.h"
#include "get_next_line.h"
#include "vector.h"

static void	trim_line_end(char *line);
static int	*process_map_info(char *line, int *width);
static int	get_map_type(char c);
static int	**init_map_data(t_data *data, t_vector *vec, int width);

int	load_map(t_data *data, char *line, int fd)
{
	int			width;
	int			max_width;
	int			*map_data;
	t_vector	*vec;

	max_width = 0;
	vec = vector_init(10, 10, 0);
	if (vec == NULL)
		return (1);
	while (line != NULL)
	{
		trim_line_end(line);
		map_data = process_map_info(line, &width);
		vector_add(vec, map_data);
		if (width > max_width)
			max_width = width;
		free(line);
		line = get_next_line(fd);
	}
	data->map.x = max_width;
	data->map.y = vec->total;
	data->map.data = init_map_data(data, vec, max_width);
	vector_cleanup(vec);
	return (0);
}

static void	trim_line_end(char *line)
{
	int	len;

	if (line[0] == '\0')
		return ;
	len = strlen(line);
	if (line[len - 1] == '\n')
		line[len - 1] = '\0';
	str_trim_end(line);
}

static int	*process_map_info(char *line, int *total)
{
	int	i;
	int	*data;

	*total = strlen(line) + 1;
	data = malloc(*total * sizeof(int));
	if (data == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '\0')
	{
		data[i] = get_map_type(line[i]);
		i++;
	}
	data[i] = MAP_END_OF_LINE;
	return (data);
}

static int	get_map_type(char c)
{
	if (c == ' ')
		return (MAP_TYPE_NOTHINGNESS);
	if (c == '0')
		return (MAP_TYPE_EMPTY_SPACE);
	if (c == '1')
		return (MAP_TYPE_WALL);
	if (c == '2')
		return (MAP_TYPE_WALL_SPRITE);
	if (c == 'P')
		return (MAP_TYPE_PORTAL);
	if (c == 'X')
		return (MAP_TYPE_EXIT);
	if (c == 'N')
		return (MAP_TYPE_N);
	if (c == 'E')
		return (MAP_TYPE_E);
	if (c == 'S')
		return (MAP_TYPE_S);
	if (c == 'W')
		return (MAP_TYPE_W);
	if (c == 'D')
		return (MAP_TYPE_DOOR);
	return (MAP_TYPE_UNKNOWN);
}

static int	**init_map_data(t_data *data, t_vector *vec, int width)
{
	int	i;
	int	**map;

	map = calloc(vec->total + 1, sizeof(int *));
	if (map == NULL)
		return (NULL);
	data->map.info = calloc(vec->total + 1, sizeof(void *));
	if (data->map.info == NULL)
	{
		free(map);
		return (NULL);
	}
	i = -1;
	while (++i < (int)vec->total)
	{
		map[i] = vector_get(vec, i);
		data->map.info[i] = calloc(width, sizeof(t_map_info));
		if (data->map.info[i] == NULL)
		{
			free(data->map.info);
			return (NULL);
		}
	}
	vec->total = 0;
	return (map);
}
