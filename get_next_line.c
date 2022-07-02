//
// get_next_line.c
//

#include <string.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*handle_eof(char ***rest, int bytes_read, int fd);
static int	read_next_block(int fd, char **rest);
static char	*prep_line(char **rest, int length);
static int	copy_buf_to_rest(char **rest, char *buf, int length);
static int	check_for_new_line(const char *string, int length);
static char	**init_static(char **rest, int fd);
static void	check_n_cleanup_static(char ***rest);
static size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize);

char	*get_next_line(int fd)
{
	char		*line;
	int			len;
	static char	**rest;

	rest = init_static (rest, fd);
	if (rest == NULL)
		return (NULL);
	if (rest[fd] != NULL)
	{
		len = check_for_new_line (rest[fd], 0);
		if (len > 0)
		{
			line = prep_line (&rest[fd], len);
			return (line);
		}
	}
	len = read_next_block (fd, &rest[fd]);
	if (len <= 0)
	{
		line = handle_eof (&rest, len, fd);
		return (line);
	}
	len = check_for_new_line (rest[fd], 0);
	line = prep_line (&rest[fd], len);
	return (line);
}

static char	*handle_eof(char ***rest, int bytes_read, int fd)
{
	char	*line;
	char	**tmp;
	int		len;

	tmp = *rest;
	if (tmp[fd] != NULL)
	{
		if (bytes_read == 0)
		{
			len = strlen(tmp[fd]);
			if (len != 0)
			{
				line = prep_line (&tmp[fd], len);
				return (line);
			}
		}
		free (tmp[fd]);
		tmp[fd] = NULL;
	}
	check_n_cleanup_static (rest);
	return (NULL);
}

// returns the number of bytes last read; -1 on error
static int	read_next_block(int fd, char **rest)
{
	char	*buf;
	int		len;
	int		bytes_read;

	buf = malloc (GNL_BUFFER_SIZE + 1);
	if (buf == NULL)
		return (-1);
	len = 0;
	while (len == 0)
	{
		bytes_read = read (fd, buf, GNL_BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			free (buf);
			return (bytes_read);
		}
		if (copy_buf_to_rest (rest, buf, bytes_read) != 0)
		{
			free (buf);
			return (-1);
		}
		len = check_for_new_line (buf, bytes_read);
	}
	free (buf);
	return (bytes_read);
}

static int	copy_buf_to_rest(char **rest, char *buf, int length)
{
	char	*tmp;
	char	*copy;
	int		len_rest;

	len_rest = 0;
	if (*rest != NULL)
		len_rest = strlen (*rest);
	tmp = *rest;
	*rest = malloc (len_rest + length + 1);
	if (*rest == NULL)
		return (-1);
	copy = *rest;
	if (tmp != NULL)
		gnl_strlcpy (copy, tmp, len_rest + 1);
	buf[length] = '\0';
	gnl_strlcpy (&copy[len_rest], buf, length + 1);
	if (tmp != NULL)
		free (tmp);
	return (0);
}

static char	*prep_line(char **rest, int length)
{
	char	*line;
	char	*tmp;
	int		len_rest;

	line = malloc (length + 1);
	if (line == NULL)
		return (NULL);
	gnl_strlcpy (line, *rest, length + 1);
	len_rest = strlen (*rest);
	tmp = *rest;
	*rest = malloc (len_rest - length + 1);
	if (*rest == NULL)
	{
		free (line);
		return (NULL);
	}
	gnl_strlcpy (*rest, &tmp[length], len_rest - length + 1);
	free (tmp);
	return (line);
}

// if length == 0, check for '\0', otherwise check length
static int	check_for_new_line(const char *string, int length)
{
	int	i;

	i = 1;
	if (length == 0)
	{
		while (*string != '\0')
		{
			if (*string == '\n')
				return (i);
			i++;
			string++;
		}
	}
	else
	{
		while (i <= length)
		{
			if (*string == '\n')
				return (i);
			i++;
			string++;
		}
	}
	return (0);
}

static char	**init_static(char **rest, int fd)
{
	char	**buf;
	int		i;

	if (rest != NULL)
		return (rest);
	if (fd < 0 || fd >= 4096)
		return (NULL);
	buf = malloc (4096 * sizeof (char *));
	if (buf == NULL)
		return (NULL);
	i = 0;
	while (i < 4096)
	{
		buf[i] = NULL;
		i++;
	}
	return (buf);
}

static void	check_n_cleanup_static(char ***rest)
{
	char	**tmp;
	int		i;

	tmp = *rest;
	i = 0;
	while (i < 4096)
	{
		if (tmp[i] != NULL)
			break ;
		i++;
	}
	if (i == 4096)
	{
		free (*rest);
		*rest = NULL;
	}
}

static size_t	gnl_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	size = strlen (src);
	if (dstsize == 0)
		return (size);
	i = 0;
	while (i < dstsize - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (size);
}
