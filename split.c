#include "monty.h"

/**
 * ft_strdup - Duplicates a string.
 * @s: The string to be duplicated.
 * Return: A newly allocated duplicate string, or NULL on failure.
 */
char *ft_strdup(char *s)
{
	int length;
	char *duplicate;
	int i;

	i = BEGIN;

	if (s == NULL)
		return (NULL);

	length = ft_strlen(s);
	duplicate = (char *)malloc((length + 1) * sizeof(char));

	if (duplicate == NULL)
		return (NULL);

	while (i < length)
	{
		duplicate[i] = s[i];
		i++;
	}

	duplicate[length] = '\0';
	return (duplicate);
}

/**
 * ft_substr - Extracts a substring from a string.
 * @str: The input string.
 * @start: The starting index of the substring.
 * @length: The length of the substring.
 * Return: A newly allocated substring, or NULL on failure.
 */
char *ft_substr(char *str, int start, int length)
{
	int str_length;
	char *substring;
	int i;

	i = BEGIN;

	if (str == NULL || start < BEGIN || length < BEGIN)
		return (NULL);

	str_length = ft_strlen(str);

	if (start >= str_length)
		return (NULL);

	if (start + length > str_length)
		length = str_length - start;

	substring = (char *)malloc((length + 1) * sizeof(char));

	if (substring == NULL)
		return (NULL);

	while (i < length)
	{
		substring[i] = str[start + i];
		i++;
	}

	substring[length] = '\0';
	return (substring);
}

/**
 * ft_count_c - Counts characters until a specified character is encountered.
 * @s: The string to be counted.
 * @c: The target character.
 * Return: The number of characters until the target character is found.
 */
size_t ft_count_c(char *s, char c)
{
	size_t i = BEGIN;

	while (s[i] && s[i] != c)
		i++;

	return (i);
}

/**
 * ft_countit - Counts occurrences of a character in a string.
 * @s: The input string.
 * @c: The target character.
 * Return: The number of occurrences of the target character in the string.
 */
size_t ft_countit(char const *s, char c)
{
	size_t i = BEGIN;
	size_t j = BEGIN;

	while (s[i])
	{
		if (s[i] != c && (s[i + NEXT] == c || s[i + NEXT] == BEGIN))
			j++;
		i++;
	}

	return (j);
}

/**
 * ft_split - Splits a string into an array of substrings based on a delimiter.
 * @s: The input string.
 * @c: The delimiter character.
 * Return: An array of substrings, or NULL on failure.
 */
char **ft_split(char const *s, char c)
{
	char **arr;
	size_t i = BEGIN;
	size_t j = ft_countit((char *)s, c);
	size_t len;

	arr = malloc(sizeof(char *) * (j + NEXT));

	if (!arr)
		return (BEGIN);

	while (*(char *)s)
	{
		if (*(char *)s != c)
		{
			len = ft_count_c((char *)s, c);
			arr[i] = ft_substr((char *)s, BEGIN, len);
			s += len;
			i++;
		}
		else
			s++;
	}

	arr[i] = BEGIN;
	return (arr);
}
