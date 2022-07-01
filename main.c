//
// main.c
//

#include <stdio.h>
#include <SDL2/SDL.h>
#include "cub3d.h"

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc < 2 || argc > 3)
	{
		printf("Error! - wrong amount of arguments!\n");
		return (1);
	}
	data = cub3d_init(argv[2]);
	if (data == nullptr)
	{
		printf("Error! - cub3d_init() failed!\n");
		return (1);
	}
	if (read_config_file(data, argv[1]) != 0 || load_textures(data) != 0)
	{
		printf("Error! - reading the config file failed!\n");
		cub3d_cleanup(data);
		return (1);
	}
	game_loop(data);
	cub3d_cleanup(data);
	return (0);
}
