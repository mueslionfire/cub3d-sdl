//
// vector.c
//

#include <stdlib.h>
#include <string.h>
#include "vector.h"

static void	*vector_resize(t_vector *vector);
static void	copy_data(t_vector *vector, void **new);

t_vector	*vector_init(size_t capacity, size_t grow_count, size_t size)
{
	t_vector	*vec;

	vec = calloc(1, sizeof(t_vector));
	if (vec == NULL)
		return (NULL);
	vec->capacity = capacity;
	vec->grow_count = grow_count;
	vec->data_size = size;
	if (size == 0)
		vec->nodes = malloc(capacity * sizeof(void *));
	else
		vec->nodes = malloc(capacity * size);
	if (vec->nodes == NULL)
	{
		free(vec);
		return (NULL);
	}
	return (vec);
}

void	vector_cleanup(t_vector *vector)
{
	size_t	i;

	if (vector == NULL)
		return ;
	i = 0;
	while (i < vector->total)
	{
		if (vector->cleanup_cb != NULL)
			vector->cleanup_cb(vector_get(vector, i));
		if (vector->data_size == 0)
			free(vector->nodes[i]);
		i++;
	}
	free(vector->nodes);
	free(vector);
}

void	vector_custom_cleanup(t_vector *vector,
			void (*vector_cleanup_cb)(void *data))
{
	vector->cleanup_cb = vector_cleanup_cb;
}

void	vector_clear(t_vector *vector)
{
	size_t	i;

	if (vector == NULL)
		return ;
	i = 0;
	while (i < vector->total)
	{
		if (vector->cleanup_cb != NULL)
			vector->cleanup_cb(vector_get(vector, i));
		if (vector->data_size == 0)
			free(vector->nodes[i]);
		i++;
	}
	vector->total = 0;
}

void	*vector_get(t_vector *vector, int index)
{
	char	*buf;

	if (index < 0 || index >= (int)vector->total)
		return (NULL);
	if (vector->data_size == 0)
		return (vector->nodes[index]);
	buf = (char *)vector->nodes;
	return (&buf[index * vector->data_size]);
}

void	*vector_add(t_vector *vector, void *data)
{
	char	*buf;

	if (vector->total == vector->capacity)
	{
		if (vector_resize(vector) == NULL)
			return (NULL);
	}
	if (vector->data_size == 0)
	{
		vector->nodes[vector->total] = data;
		vector->total++;
		return (vector->nodes[vector->total - 1]);
	}
	buf = (char *)vector->nodes;
	memcpy(&buf[vector->total * vector->data_size], data,
		vector->data_size);
	vector->total++;
	return (&buf[(vector->total - 1) * vector->data_size]);
}

static void	*vector_resize(t_vector *vector)
{
	size_t	new_capacity;
	void	**new;

	new_capacity = vector->capacity + vector->grow_count;
	if (vector->data_size == 0)
		new = malloc(new_capacity * sizeof(void *));
	else
		new = malloc(new_capacity * vector->data_size);
	if (new == NULL)
		return (NULL);
	copy_data(vector, new);
	free(vector->nodes);
	vector->nodes = new;
	vector->capacity = new_capacity;
	return (vector->nodes);
}

static void	copy_data(t_vector *vector, void **new)
{
	size_t	i;

	if (vector->data_size == 0)
	{
		i = 0;
		while (i < vector->total)
		{
			new[i] = vector->nodes[i];
			i++;
		}
		return ;
	}
	memcpy(new, vector->nodes, vector->total * vector->data_size);
}

void	vector_delete(t_vector *vec, int idx)
{
	char	*buf;
	size_t	i;

	if (idx < 0 || idx >= (int)vec->total)
		return ;
	if (vec->data_size == 0)
	{
		vec->cleanup_cb(vec->nodes[idx]);
		free(vec->nodes[idx]);
		i = idx;
		while (i < vec->total - 1)
		{
			vec->nodes[i] = vec->nodes[i + 1];
			i++;
		}
		vec->nodes[i + 1] = NULL;
	}
	else
	{
		buf = (char *)vec->nodes;
		vec->cleanup_cb(&buf[idx * vec->data_size]);
		memmove(&buf[idx * vec->data_size], &buf[(idx + 1) * vec->data_size],
			(vec->total - (idx + 1)) * vec->data_size);
	}
	vec->total--;
}
