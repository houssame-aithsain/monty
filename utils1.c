#include "monty.h"

/**
 * argChecker - Check if a string is a valid argument for push.
 * @str: String to be checked.
 * Return: true if valid, false otherwise.
 */
bool argChecker(char *str)
{
	if (!str)
		return (false);

	if (str[BEGIN] && is_op(str[BEGIN]) && str[NEXT] >= '0' && str[NEXT] <= '9')
		return (true);

	return (str[BEGIN] >= '0' && str[BEGIN] <= '9');
}
