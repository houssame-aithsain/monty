#include "monty.h"

/**
 * ft_strcmp - Compares two strings lexicographically.
 * @s1: The first string.
 * @s2: The second string.
 * Return: 0 if strings are equal, a negative value if s1 < s2
 */
int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * ft_free - Frees memory allocated for an array of strings.
 * @src: The array of strings.
 * @line: The individual string to be freed.
 */
void ft_free(char **src, char *line)
{
	int i = 0;

	free(line);

	while (src && src[i])
		free(src[i++]);

	free(src);
}

/**
 * printError - Prints error messages based on opcode and line number.
 * @opc: The opcode causing the error.
 * @line_n: The line number where the error occurred.
 * @flag: The type of error to be printed.
 * @line: line
 * @stack: stack
 */
void printError(char **opc, char *line, int line_n,
	stack_t *stack, int flag)
{
	if (!opc[BEGIN] || !opc[BEGIN][BEGIN])
		return;

	switch (flag)
	{
	case DEFAULTERR:
		fprintf(stderr, "L<%d>: unknown instruction <%s>\n", line_n, opc[BEGIN]);
		break;
	case PUSHERR:
		fprintf(stderr, "L<%d>: usage: push integer\n", line_n);
	default:
		break;
	}
	ft_free(opc, line);
	stackFree(stack);
	exit(EXIT_FAILURE);
}

/**
 * newLineEraser - Replaces newline characters in a string with null.
 * @src: The source string.
 * Return: The modified string.
 */
char *newLineEraser(char *src)
{
	int i = 0;

	while (src && src[i])
	{
		if (src[i] == NEWLINE)
			src[i] = '\0';
		i++;
	}

	return (src);
}

/**
 * stackFree - Frees the memory allocated for a stack of integers.
 * @stack: The stack to be freed.
 */
void stackFree(stack_t *stack)
{
	stack_t *tmp;

	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
}
