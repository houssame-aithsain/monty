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
 * getFileDescriptorId - Get the file descriptor ID for a file.
 * @fileName: Name of the file.
 * Return: File descriptor ID.
 */
int getFileDescriptorId(char *fileName)
{
	int fd = open(fileName, O_RDONLY);

	if (!is_valide_fd(fd))
	{
		fprintf(stderr, "%s %s\n", FDERR, fileName);
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
			if (prePush(&data, tmpOpcode))
				continue;
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
