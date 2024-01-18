#include "monty.h"

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
			printError(tmpOpcode, data->line, data->ln, data->stack, PUSHERR);
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
