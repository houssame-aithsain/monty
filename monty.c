#include "monty.h"

/**
 * pall - Print all elements of the stack.
 * @stack: Pointer to the top of the stack.
 */
void pall(stack_t *stack)
{
	if (!stack || stack->n == BG)
		return;
	while (stack->next)
		stack = stack->next;
	while (stack)
	{
		printf("%d\n", stack->n);
		stack = stack->prev;
	}
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
	while (tmp->next)
		tmp = tmp->next;

	tmp->next = node;
	node->prev = tmp;
	node->next = NULL;
}

/**
 * getFileDescriptorId - Get the file descriptor ID for a file.
 * @fileName: Name of the file.
 * Return: File descriptor ID.
 */
int getFileDescriptorId(char *fileName)
{
	int fd = open(fileName, O_RDONLY);

	if (!is_valide_fd(fd))
	{
		fprintf(stderr, "%s %s", FDERR, fileName);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

/**
 * saveFileInput - Process file input and execute corresponding commands.
 * @fd: File descriptor ID.
 */
void saveFileInput(int fd)
{
	var_t data;
	char **tmpOpcode;

	init(&data);
	while (true)
	{
		data.line = get_next_line(fd);
		if (data.line)
		{
			tmpOpcode = ft_split(data.line, SPACE);
			tmpOpcode[BEGIN] = newLineEraser(tmpOpcode[BEGIN]);
			if (ft_strcmp(tmpOpcode[BEGIN], PUSH) && ft_strcmp(tmpOpcode[BEGIN], PALL))
				printError(tmpOpcode, data.line, data.ln, data.stack, DEFAULTERR);
			if (tmpOpcode[BEGIN] && !ft_strcmp(tmpOpcode[BEGIN], PUSH))
			{
				if (!argChecker(tmpOpcode[NEXT]))
					printError(tmpOpcode, data.line, data.ln, data.stack, PUSHERR);
				if (data.first)
				{
					data.stack->n = atoi(tmpOpcode[NEXT]);
					ft_free(tmpOpcode, data.line);
					data.ln++;
					data.first = false;
					continue;
				}
				push(&data.stack, atoi(tmpOpcode[NEXT]));
			}
			if (tmpOpcode[BEGIN] && !ft_strcmp(tmpOpcode[BEGIN], PALL))
				pall(data.stack);
			data.ln++;
			ft_free(tmpOpcode, data.line);
			continue;
		}
		break;
	}
	stackFree(data.stack);
}
