//
// cub3d.h
//

#ifndef CUB3D_H
#define CUB3D_H

#include <SDL2/SDL.h>

#define nullptr NULL
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_NAME_LEN 32
#define TEX_WIDTH 256
#define TEX_HEIGHT 256

#define LEVEL_1 "./maps/level1.cub"
#define LEVEL_2 "./maps/level2.cub"
#define LEVEL_3 "./maps/level3.cub"

typedef enum e_info_type
{
	INFO_TYPE_NO = 0,
	INFO_TYPE_EA,
	INFO_TYPE_SO,
	INFO_TYPE_WE,
	INFO_TYPE_FLOOR,
	INFO_TYPE_CEILING,
	INFO_TYPE_EMPTY,
	INFO_TYPE_MAP,
}				t_info_type;

typedef enum e_map_type
{
	MAP_TYPE_UNKNOWN = -2,
	MAP_TYPE_NOTHINGNESS = -1,
	MAP_TYPE_EMPTY_SPACE = 0,
	MAP_TYPE_WALL,
	MAP_TYPE_WALL_SPRITE,
	MAP_TYPE_PORTAL,
	MAP_TYPE_EXIT,
	MAP_TYPE_DOOR,
	MAP_TYPE_N,
	MAP_TYPE_E,
	MAP_TYPE_S,
	MAP_TYPE_W,
	MAP_END_OF_LINE,
}				t_map_type;

typedef struct s_vec
{
	double	x;
	double	y;
}				t_vec;

typedef struct s_vec_i
{
	int	x;
	int	y;
}				t_vec_i;

typedef struct s_rect
{
	int	width;
	int	height;
	int	x0;
	int	y0;
	int	color;
}				t_rect;

typedef struct s_start
{
	uint64_t	start_time;
	int			start_flag;
}				t_start;

typedef struct	s_surfaces
{
	SDL_Surface	*start_screen;
	SDL_Surface *tex_north;
	SDL_Surface *tex_east;
	SDL_Surface *tex_south;
	SDL_Surface *tex_west;
	SDL_Surface *tex_portal[5];
	SDL_Surface *tex_torch[5];
	SDL_Surface *tex_door;
	SDL_Surface *tex_exit;
}				t_surfaces;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_map_info
{
	int			open_door;
	int			visible;
	int			frame_num;
	uint64_t	sprite_time;
}				t_map_info;

typedef struct s_map
{
	char		*tx_no;
	char		*tx_ea;
	char		*tx_so;
	char		*tx_we;
	int			**data;
	t_map_info	**info;
	int			x;
	int			y;
	t_color		ceiling;
	t_color		flr;
}				t_map;

typedef struct s_minimap
{
	int		width;
	int		height;
}				t_minimap;

typedef struct s_data
{
	char			*level;
	char			user_name[MAX_NAME_LEN];
	double			move_speed;
	double			rot_speed;
	int				new_level;
	int				exit;
	int				frames;
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*framebuffer;
	t_map			map;
	t_minimap		minimap;
	t_start			start;
	t_surfaces		surfaces;
	t_vec			pos;
	t_vec			dir;
	t_vec			camera_plane;
	t_vec_i			mouse_pos;
	uint32_t		*pixels;
	uint64_t		initial_time;
	uint64_t		current_time;
	uint64_t		last_time;
	uint64_t		frame_time;
}				t_data;

// init.c
t_data	*cub3d_init(const char *user_name);

// cleanup.c
void	cub3d_cleanup(t_data *data);
void	free_map(t_data *data);

// game_loop.c
void	game_loop(t_data *data);

// utils.c
void	cub3d_pixel_put(t_data *data, int x, int y, int color);
void	str_trim_end(char *line);
long long	get_time(void);
void	ft_bzero64(void *s, size_t n);
int		create_trgb(int t, int r, int g, int b);
int		get_color_from_surface(SDL_Surface *surface, int offset);
size_t	cub3d_strlcpy(char *dst, const char *src, size_t dstsize);

// sdl_utils.c
SDL_Surface	*load_surface(const char *path);

// start_screen.c
void	render_start_screen(t_data *data);

// config_file.c
int		read_config_file(t_data *data, char *filename);

// config_check.c
int		check_input(t_data *data);

// config_info.c
int		get_type_identifier(char *input);
int		get_type_info(t_map *map, char *input, int type);

// config_map.c
int		load_map(t_data *data, char *line, int fd);

// textures.c
int		load_textures(t_data *data);

// run.c
void	run(t_data *data);

// minimap.c
void	render_minimap(t_data *data);

// raycast.c
int		raycast(t_data *data);

// input.c
int		key_cb(t_data *data, int keycode);
int		mouse_cb(t_data *data);
int		end_loop(t_data *data);

// keys.c
void	key_w(t_data *data);
void	key_a(t_data *data);
void	key_d(t_data *data);
void	key_s(t_data *data);
void	key_left(t_data *data);
void	key_right(t_data *data);
void	key_f(t_data *data);

#endif // CUB3D_H
