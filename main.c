#include "monty.h"

/**
 * main - Entry point of the Monty interpreter.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure.
 */
int main(int argc, char **argv)
{
	if (argc == ARGV_NUMB)
		saveFileInput(getFileDescriptorId(argv[NEXT]));
	else
	{
		fprintf(stderr, "%s\n", USAGE);
		exit(EXIT_FAILURE);
	}

	return (EXIT_SUCCESS);
}
