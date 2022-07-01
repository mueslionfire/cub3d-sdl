//
// textures.c
//

#include "cub3d.h"

static int	load_wall_textures(t_data *data);
static int	load_torch_sprites(t_data *data);
static int	load_portal_sprites(t_data *data);
static int	load_extra_textures(t_data *data);

int	load_textures(t_data *data)
{
	if (load_wall_textures(data) != 0)
		return (1);
	if (load_extra_textures(data) != 0)
		return (1);
	if (load_torch_sprites(data) != 0)
		return (1);
	if (load_portal_sprites(data) != 0)
		return (1);
	return (0);
}

static int	load_wall_textures(t_data *data)
{
	data->surfaces.tex_north = load_surface(data->map.tx_no);
	data->surfaces.tex_east = load_surface(data->map.tx_ea);
	data->surfaces.tex_south = load_surface(data->map.tx_so);
	data->surfaces.tex_west = load_surface(data->map.tx_we);
	if (data->surfaces.tex_north == nullptr || data->surfaces.tex_east == nullptr
		|| data->surfaces.tex_south == nullptr || data->surfaces.tex_west == nullptr)
		return (1);
	return (0);
}

static int	load_torch_sprites(t_data *data)
{
	data->surfaces.tex_torch[0] = load_surface("./textures/torch_frame1.png");
	data->surfaces.tex_torch[1] = load_surface("./textures/torch_frame2.png");
	data->surfaces.tex_torch[2] = load_surface("./textures/torch_frame3.png");
	data->surfaces.tex_torch[3] = load_surface("./textures/torch_frame4.png");
	data->surfaces.tex_torch[4] = load_surface("./textures/torch_frame5.png");
	if (data->surfaces.tex_torch[0] == nullptr || data->surfaces.tex_torch[1] == nullptr
		|| data->surfaces.tex_torch[2] == nullptr || data->surfaces.tex_torch[3] == nullptr
		|| data->surfaces.tex_torch[4] == nullptr)
		return (1);
	return (0);
}

static int	load_portal_sprites(t_data *data)
{
	data->surfaces.tex_portal[0] = load_surface("./textures/portal_frame1.png");
	data->surfaces.tex_portal[1] = load_surface("./textures/portal_frame2.png");
	data->surfaces.tex_portal[2] = load_surface("./textures/portal_frame3.png");
	data->surfaces.tex_portal[3] = load_surface("./textures/portal_frame4.png");
	data->surfaces.tex_portal[4] = load_surface("./textures/portal_frame5.png");
	if (data->surfaces.tex_portal[0] == nullptr || data->surfaces.tex_portal[1] == nullptr
		|| data->surfaces.tex_portal[2] == nullptr || data->surfaces.tex_portal[3] == nullptr
		|| data->surfaces.tex_portal[4] == nullptr)
		return (1);
	return (0);
}

static int	load_extra_textures(t_data *data)
{
	data->surfaces.tex_door = load_surface("./textures/door.png");
	if (data->surfaces.tex_door == nullptr)
		return (1);
	data->surfaces.tex_exit = load_surface("./textures/exit.png");
	if (data->surfaces.tex_exit == nullptr)
		return (1);
	return (0);
}
