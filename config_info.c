//
// config_info.c
//

#include <string.h>
#include "cub3d.h"

static int	check_file_info(t_map *map, int type);
static int	get_color_value(t_color	*color, char *input);
static int	get_next_rgb_value(char **input);

int	get_type_identifier(char *input)
{
	if (strncmp(input, "NO ", 3) == 0)
		return (INFO_TYPE_NO);
	if (strncmp(input, "EA ", 3) == 0)
		return (INFO_TYPE_EA);
	if (strncmp(input, "SO ", 3) == 0)
		return (INFO_TYPE_SO);
	if (strncmp(input, "WE ", 3) == 0)
		return (INFO_TYPE_WE);
	if (strncmp(input, "F ", 2) == 0)
		return (INFO_TYPE_FLOOR);
	if (strncmp(input, "C ", 2) == 0)
		return (INFO_TYPE_CEILING);
	while (*input != '\0' && *input != '\n')
	{
		if (isspace(*input) == 0)
			return (INFO_TYPE_MAP);
		input++;
	}
	return (INFO_TYPE_EMPTY);
}

int	get_type_info(t_map *map, char *input, int type)
{
	if (input[0] != '\0' && input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';
	str_trim_end(input);
	if (type >= INFO_TYPE_NO && type <= INFO_TYPE_WE)
		input += 2;
	else if (type == INFO_TYPE_FLOOR || type == INFO_TYPE_CEILING)
		input++;
	while (*input == ' ')
		input++;
	if (check_file_info(map, type) != 0)
		return (-1);
	if (type == INFO_TYPE_NO)
		map->tx_no = strdup(input);
	else if (type == INFO_TYPE_EA)
		map->tx_ea = strdup(input);
	else if (type == INFO_TYPE_SO)
		map->tx_so = strdup(input);
	else if (type == INFO_TYPE_WE)
		map->tx_we = strdup(input);
	else if (type == INFO_TYPE_FLOOR)
		return (get_color_value(&map->flr, input));
	else if (type == INFO_TYPE_CEILING)
		return (get_color_value(&map->ceiling, input));
	return (0);
}

static int	check_file_info(t_map *map, int type)
{
	if ((type == INFO_TYPE_NO && map->tx_no != NULL)
		|| (type == INFO_TYPE_EA && map->tx_ea != NULL)
		|| (type == INFO_TYPE_SO && map->tx_so != NULL)
		|| (type == INFO_TYPE_WE && map->tx_we != NULL))
		return (-1);
	if (type == INFO_TYPE_FLOOR)
	{
		if (map->flr.r != -1 || map->flr.g != -1 || map->flr.b != -1)
			return (-1);
	}
	else if (type == INFO_TYPE_CEILING)
	{
		if (map->ceiling.r != -1 || map->ceiling.g != -1
			|| map->ceiling.b != -1)
			return (-1);
	}
	return (0);
}

static int	get_color_value(t_color	*color, char *input)
{
	if (isdigit(*input) == 0)
		return (-1);
	color->r = get_next_rgb_value(&input);
	if (*input != '\0')
	{
		color->g = get_next_rgb_value(&input);
		if (*input != '\0')
		{
			color->b = get_next_rgb_value(&input);
			if (color->r != -1 && color->g != -1 && color->b != -1)
				return (0);
		}
	}
	return (-1);
}

static int	get_next_rgb_value(char **input)
{
	int	value;

	if (**input == ',')
		(*input)++;
	if (**input == '\0')
		return (-1);
	value = 0;
	while (**input != '\0' && **input != ',')
	{
		if (isdigit(**input) == 0)
			return (-1);
		value *= 10;
		value += (**input - '0');
		if (value > 255)
			return (-1);
		(*input)++;
	}
	return (value);
}
