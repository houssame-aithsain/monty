#include "monty.h"

/**
 * add - Adds the top two elements of the stack.
 * @opcode: An array containing the opcode (not used in the function).
 * @data: A pointer to the structure holding program data.
 */
void add(char **opcode, var_t *data)
{
	stack_t *tmp = data->stack;
	int count = NEXT;

	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	if (!data->stack || data->stack->n == BG || count < 2)
		printError(opcode, data, ADDERR);
	count = tmp->n;
	while (data->stack->next)
	{
		if (data->stack->next == tmp)
		{
			data->stack->next = NULL;
			free(tmp);
			break;
		}
		data->stack = data->stack->next;
	}
	data->stack->n += count;
	while (data->stack && data->stack->prev)
		data->stack = data->stack->prev;
}

/**
 * swap - Swaps the top two elements of the stack.
 * @opcode: An array containing the opcode (not used in the function).
 * @data: A pointer to the structure holding program data.
 */
void swap(char **opcode, var_t *data)
{
	stack_t *tmp = data->stack;
	int count = NEXT;

	while (tmp->next)
	{
		count++;
		tmp = tmp->next;
	}
	if (!data->stack || data->stack->n == BG || count < 2)
		printError(opcode, data, SWAPERR);
	count = tmp->n;
	tmp->n =  tmp->prev->n;
	tmp->prev->n = count;
}

/**
 * push - Push a new element onto the stack.
 * @stack: Pointer to the top of the stack.
 * @numb: Number to be pushed onto the stack.
 */
void push(stack_t **stack, unsigned int numb)
{
	stack_t *tmp = *stack;
	stack_t *node = ft_malloc();

	node->n = numb;
	if (!*stack)
	{
		*stack = node;
		node->next = NULL;
		node->prev = NULL;
		return;
	}
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = node;
	node->prev = tmp;
	node->next = NULL;
}

/**
 * prePush - Processes the "push" opcode before pushing a value onto the stack.
 * @data: A pointer to the structure holding program data.
 * @tmpOpcode: An array containing parsed opcode and argument.
 * Return: True if the push operation is successful, false otherwise.
 */
bool prePush(var_t *data, char **tmpOpcode)
{
	if (tmpOpcode[BEGIN] && !ft_strcmp(tmpOpcode[BEGIN], PUSH))
	{
		if (!argChecker(tmpOpcode[NEXT]))
			printError(tmpOpcode, data, PUSHERR);
		if (data->first)
		{
			data->stack->n = atoi(tmpOpcode[NEXT]);
			ft_free(tmpOpcode, data->line);
			data->ln++;
			data->first = false;
			return (true);
		}
		push(&data->stack, atoi(tmpOpcode[NEXT]));
	}
	return (false);
}
