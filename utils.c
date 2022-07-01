//
// utils.c
//

#include <sys/time.h>
#include "cub3d.h"

inline void	cub3d_pixel_put(t_data *data, int x, int y, int color)
{
	data->pixels[y * SCREEN_WIDTH + x] = color;
}

void	str_trim_end(char *line)
{
	int	count;

	if (line == NULL)
		return ;
	if (*line == '\0')
		return ;
	count = 0;
	while (*line != '\0')
	{
		count++;
		line++;
	}
	line--;
	while (count > 0 && isspace(*line) == 1)
	{
		*line = '\0';
		line--;
		count--;
	}
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		milliseconds;

	gettimeofday(&tv, NULL);
	milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000;
	return (milliseconds);
}

void	ft_bzero64(void *s, size_t n)
{
	uint64_t	*data;

	if (n == 0)
		return ;
	if (n % sizeof(uint64_t) != 0)
		return ;
	data = s;
	n /= sizeof(uint64_t);
	while (n > 0)
	{
		*data = 0;
		data++;
		n--;
	}
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_color_from_surface(SDL_Surface *surface, int offset)
{
	int	*pixels;

	pixels = (int *)surface->pixels;
	return pixels[offset];
}
