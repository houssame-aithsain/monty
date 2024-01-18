#include "monty.h"

/**
 * ft_strlen - Returns the length of a null-terminated string.
 * @str: The input string.
 * Return: The length of the string.
 */
size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

/**
 * ft_strjoin - Concatenates two strings dynamically, freeing the first string.
 * @s1: The first string.
 * @s2: The second string.
 * Return: A new string resulting from the concatenation.
 */
char *ft_strjoin(char *s1, char *s2)
{
	char *arr;
	size_t i;
	size_t j;
	size_t k;
	size_t m;

	k = -1;
	m = 0;
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (i + j == 0)
	{
		free(s1);
		return (NULL);
	}
	arr = malloc(i + j + 1);
	while (++k < i)
		arr[k] = s1[k];
	while (k < (i + j))
		arr[k++] = s2[m++];
	arr[k] = '\0';
	free(s1);
	return (arr);
}

/**
 * ft_check_new_line - Checks if a newline character.
 * @buffer: The input buffer.
 * Return: 1 if newline is present, 0 otherwise.
 */
int ft_check_new_line(char *buffer)
{
	size_t i = 0;

	while (buffer[i])
	{
		if (buffer[i] == '\n')
			return (false);
		i++;
	}
	return (true);
}
