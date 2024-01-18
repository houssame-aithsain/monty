#include "monty.h"

/**
 * argChecker - Check if a string is a valid argument for push.
 * @str: String to be checked.
 * Return: true if valid, false otherwise.
 */
bool argChecker(char *str)
{
	int i = 0;

	str = newLineEraser(str);
	if (!str)
		return (false);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
