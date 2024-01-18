#include "monty.h"

/**
 * pall - Print all elements of the stack.
 * @stack: Pointer to the top of the stack.
 */
void pall(stack_t *stack)
{
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
	char *line;
	char **tmpOpcode;
	int line_number = NEXT;
	stack_t *stack;

	stack = ft_malloc();
	stack->prev = NULL;
	stack->next = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (line)
		{
			tmpOpcode = ft_split(line, SPACE);
			tmpOpcode[BEGIN] = newLineEraser(tmpOpcode[BEGIN]);
			if (ft_strcmp(tmpOpcode[BEGIN], PUSH) && ft_strcmp(tmpOpcode[BEGIN], PALL))
				printError(tmpOpcode, line, line_number, stack, DEFAULTERR);
			if (tmpOpcode[BEGIN] && !ft_strcmp(tmpOpcode[BEGIN], PUSH))
			{
				if (!argChecker(tmpOpcode[NEXT]))
					printError(tmpOpcode, line, line_number, stack, PUSHERR);
				if (line_number == NEXT)
				{
					stack->n = atoi(tmpOpcode[NEXT]);
					ft_free(tmpOpcode, line);
					line_number++;
					continue;
				}
				push(&stack, atoi(tmpOpcode[NEXT]));
			}
			if (tmpOpcode[BEGIN] && !ft_strcmp(tmpOpcode[BEGIN], PALL))
				pall(stack);
			line_number++;
			ft_free(tmpOpcode, line);
			continue;
		}
		break;
	}
	stackFree(stack);
}
