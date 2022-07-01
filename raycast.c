//
// raycast.c
//

#include "cub3d.h"

int	raycast(t_data *data)
{
	double	camera_x;
	double	perp_wall_distance; // perpendicular
	double	frame_time;
	int		x;
	int		hit;
	int		draw_start;
	int		draw_end;
	int		line_height;
	int		side;
	int		color;
	int		frame;
	t_vec	ray_dir;
	t_vec	side_distance;
	t_vec	delta_distance;
	t_vec_i	step;
	t_vec_i	map;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		ray_dir.x = data->dir.x + data->camera_plane.x * camera_x;
		ray_dir.y = data->dir.y + data->camera_plane.y * camera_x;
		map.x = (int)data->pos.x;
		map.y = (int)data->pos.y;
		
		if (ray_dir.x == 0)
			delta_distance.x = INFINITY;
		else
			delta_distance.x = fabs(1/ ray_dir.x);
		if (ray_dir.y == 0)
			delta_distance.y = INFINITY;
		else
			delta_distance.y = fabs(1/ ray_dir.y);
		if (ray_dir.x < 0)
		{
			step.x = -1;
			side_distance.x = (data->pos.x - map.x) * delta_distance.x;
		}
		else
		{
			step.x = 1;
			side_distance.x = (map.x + 1.0 - data->pos.x) * delta_distance.x;
		}
		if (ray_dir.y < 0)
		{
			step.y = -1;
			side_distance.y = (data->pos.y - map.y) * delta_distance.y;
		}
		else
		{
			step.y = 1;
			side_distance.y = (map.y + 1.0 - data->pos.y) * delta_distance.y;
		}
		hit = 0;
		while (hit == 0)
		{
			if (side_distance.x < side_distance.y)
			{
				side_distance.x += delta_distance.x;
				map.x += step.x;
				side = 0; // East/West
			}
			else
			{
				side_distance.y += delta_distance.y;
				map.y += step.y;
				side = 1; // North/South
			}
			if (data->map.data[map.y][map.x] > 0)
			{
				if (data->map.data[map.y][map.x] == MAP_TYPE_DOOR)
				{
					if (data->map.info[map.y][map.x].open_door == 0)
						hit = 1;
				}
				else
					hit = 1;
			}
		}
		if (side == 0)
			perp_wall_distance = side_distance.x - delta_distance.x;
		else
			perp_wall_distance = side_distance.y - delta_distance.y;
		line_height = (int)(SCREEN_HEIGHT / perp_wall_distance);
		draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
		if (draw_end >= SCREEN_HEIGHT)
			draw_end = SCREEN_HEIGHT - 1;

		double	wall_x;

		if (side == 0)
			wall_x = data->pos.y + perp_wall_distance * ray_dir.y;
		else
			wall_x = data->pos.x + perp_wall_distance * ray_dir.x;
		wall_x -= floor(wall_x);

		int	tex_x;
		tex_x = (int)(wall_x * (double)TEX_WIDTH);
		if (side == 0 && ray_dir.x > 0)
			tex_x = TEX_WIDTH - tex_x - 1;
		if (side == 1 && ray_dir.y < 0)
			tex_x = TEX_WIDTH - tex_x - 1;

		double step = 1.0 * TEX_HEIGHT / line_height;
		double tex_pos = (draw_start - SCREEN_HEIGHT / 2 + line_height / 2) * step;
		int y = -1;
		int tex_y;
		while (++y < SCREEN_HEIGHT)
		{
			if (y < draw_start)
				color = create_trgb(0, data->map.ceiling.r, data->map.ceiling.g, data->map.ceiling.b);
			else if (y >= draw_start && y <= draw_end)
			{
				tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
				tex_pos += step;
				if (data->map.data[map.y][map.x] == MAP_TYPE_DOOR
					&& data->map.info[map.y][map.x].open_door == 0)
				{
					color = get_color_from_surface(data->surfaces.tex_door, TEX_HEIGHT * tex_y + tex_x);
					//color = data->tx_door.data[TEX_HEIGHT * tex_y + tex_x];
					if (side == 1)
						color = (color >> 1) & 8355711;
				}
				else
				{
					if (side == 1)
					{					
						if (ray_dir.y > 0)
							color = get_color_from_surface(data->surfaces.tex_south, TEX_HEIGHT * tex_y + tex_x);
						else
							color = get_color_from_surface(data->surfaces.tex_north, TEX_HEIGHT * tex_y + tex_x);
						color = (color >> 1) & 8355711; // shadow
					}
					else
					{
						if (ray_dir.x < 0)
							color = get_color_from_surface(data->surfaces.tex_west, TEX_HEIGHT * tex_y + tex_x);
						else
							color = get_color_from_surface(data->surfaces.tex_east, TEX_HEIGHT * tex_y + tex_x);
					}
				}
				if (data->map.data[map.y][map.x] == MAP_TYPE_WALL_SPRITE)
				{
					frame = data->map.info[map.y][map.x].frame_num;
					if (get_color_from_surface(data->surfaces.tex_torch[frame], TEX_HEIGHT * tex_y + tex_x) != (int)0xFF000000)
						color = get_color_from_surface(data->surfaces.tex_torch[frame], TEX_HEIGHT * tex_y + tex_x);
				}
			}
			else
				color = create_trgb(0, data->map.flr.r, data->map.flr.g, data->map.flr.b);
			cub3d_pixel_put(data, x, y, color);
		}
		x++;
	}
	render_minimap(data);

	data->last_time = data->current_time;
	data->current_time = get_time();
	frame_time = 1000 / (data->current_time - data->last_time); // seconds
	// printf("Frame time: %f\n", frame_time);
	data->move_speed = (frame_time / 1000) * 5.0;
	data->rot_speed = (frame_time / 1000) * 3.0;
	return (0);
}
