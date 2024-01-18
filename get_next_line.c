#include "monty.h"

/**
 * get_after_new_line - Extracts the content after the newline.
 * @c: The input string.
 * Return: A newly allocated string containing the content after the newline.
 */
char *get_after_new_line(char *c)
{
	char *arr;
	size_t i, j, m, f;

	m = BEGIN;
	i = BEGIN;
	j = ft_strlen(c);

	while (c && c[i] && c[i] != '\n')
		i++;

	if (!c || !c[i] || (c[i] == '\n' && c[i + NEXT] == '\0'))
	{
		free(c);
		return (NULL);
	}

	i++;
	f = i;
	arr = malloc((j - i) + NEXT);

	while (m < j - i)
		arr[m++] = c[f++];

	arr[m] = BEGIN;
	free(c);
	return (arr);
}

/**
 * get_befor_new_line - Extracts the content before the newline.
 * @container: The input string.
 * Return: A newly allocated string containing the content before the newline.
 */
char *get_befor_new_line(char *container)
{
	char *arr;
	size_t i, j;

	if (!container)
		return (NULL);

	i = BEGIN;
	j = BEGIN;

	while (container[i] && container[i] != '\n')
		i++;

	if (container[i] == '\n')
		i++;

	arr = malloc(i + NEXT);

	if (!arr)
		return (NULL);

	while (j < i)
	{
		arr[j] = container[j];
		j++;
	}

	arr[j] = BEGIN;
	return (arr);
}

/**
 * get_line_copy - Reads from a file descriptor and copies lines.
 * @fd: The file descriptor.
 * @container: The current content.
 * Return: A newly allocated string with appended content, or NULL on error.
 */
char *get_line_copy(int fd, char *container)
{
	char *buffer;
	int size;

	size = NEXT;
	buffer = malloc(BUFFER_SIZE + NEXT);

	if (!buffer)
		return (NULL);

	while (size > BEGIN)
	{
		size = read(fd, buffer, BUFFER_SIZE);

		if (size == -NEXT)
		{
			free(container);
			free(buffer);
			return (BEGIN);
		}

		buffer[size] = BEGIN;
		container = ft_strjoin(container, buffer);

		if (!ft_check_new_line(buffer))
			break;
	}

	free(buffer);
	return (container);
}

/**
 * get_next_line - Reads the next line from a file descriptor.
 * @fd: The file descriptor.
 * Return: A newly allocated string containing the next line.
 */
char *get_next_line(int fd)
{
	static char *container;
	char *holder;

	if (fd < BEGIN || BUFFER_SIZE <= BEGIN)
		return (BEGIN);

	if (!container)
	{
		container = malloc(NEXT);

		if (!container)
			return (NULL);

		container[BEGIN] = '\0';
	}

	container = get_line_copy(fd, container);
	holder = get_befor_new_line(container);
	container = get_after_new_line(container);

	if (!holder)
	{
		free(container);
		return (NULL);
	}

	return (holder);
}
