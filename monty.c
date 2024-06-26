#include "monty.h"

/**
 * pop - Removes the top element from the stack.
 * @opcode: An array containing the opcode (not used in the function).
 * @data: A pointer to the structure holding program data.
 */
void pop(char **opcode, var_t *data)
{
	stack_t *tmp = data->stack;

	if (!tmp || tmp->n == BG)
		printError(opcode, data, POPERR);
	while (tmp->next)
		tmp = tmp->next;
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
	if (data->stack == tmp)
	{
		free(data->stack);
		data->stack = NULL;
	}
	while (data->stack && data->stack->prev)
		data->stack = data->stack->prev;
}

/**
 * pint - Prints the value at the top of the stack.
 * @opcode: An array containing the opcode (not used in the function).
 * @data: A pointer to the structure holding program data.
 */
void pint(char **opcode, var_t *data)
{
	stack_t *tmp = data->stack;

	if (!tmp || tmp->n == BG)
		printError(opcode, data, PINTERR);
	while (tmp->next)
		tmp = tmp->next;
	printf("%d\n", tmp->n);
}

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
	char **opcode;

	init(&data);
	while (true)
	{
		data.line = get_next_line(fd);
		if (data.line)
		{
			opcode = ft_split(data.line, SPACE);
			opcode[BEGIN] = newLineEraser(opcode[BEGIN]);
			if (ft_strcmp(opcode[BEGIN], PUSH) && ft_strcmp(opcode[BEGIN], PALL)
				&& ft_strcmp(opcode[BEGIN], PINT) && ft_strcmp(opcode[BEGIN], POP)
				&& ft_strcmp(opcode[BEGIN], SWAP) && ft_strcmp(opcode[BEGIN], ADD)
				&& ft_strcmp(opcode[BEGIN], NOP))
				printError(opcode, &data, DEFAULTERR);
			if (prePush(&data, opcode))
				continue;
			if (opcode[BEGIN] && !ft_strcmp(opcode[BEGIN], PALL))
				pall(data.stack);
			if (opcode[BEGIN] && !ft_strcmp(opcode[BEGIN], PINT))
				pint(opcode, &data);
			if (opcode[BEGIN] && !ft_strcmp(opcode[BEGIN], POP))
				pop(opcode, &data);
			if (opcode[BEGIN] && !ft_strcmp(opcode[BEGIN], SWAP))
				swap(opcode, &data);
			if (opcode[BEGIN] && !ft_strcmp(opcode[BEGIN], ADD))
				add(opcode, &data);
			data.ln++;
			ft_free(opcode, data.line);
			continue;
		}
		break;
	}
	stackFree(data.stack);
}
