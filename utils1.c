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
	if (!str || !str[BEGIN])
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

/**
 * ft_malloc - Check if a string is a valid argument for push.
 * Return: true if valid, false otherwise.
 */
stack_t *ft_malloc(void)
{
	stack_t *stack;

	stack = malloc(sizeof(stack) * 3);
	if (!stack)
	{
		fprintf(stderr, MALLOCERR);
		exit(EXIT_FAILURE);
	}
	return (stack);
}

/**
 * init - Initializes a structure with default values.
 * @data: A pointer to the structure to be initialized.
 */
void init(var_t *data)
{
	data->line = NULL;
	data->ln = NEXT;
	data->first = true;
	data->stack = ft_malloc();
	data->stack->prev = NULL;
	data->stack->next = NULL;
	data->stack->n = BG;
}
