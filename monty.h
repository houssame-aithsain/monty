#ifndef MONTY_H
#define MONTY_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define USAGE "USAGE: monty file"
#define FDERR "Error: Can't open file"
#define PUSH "push"
#define PALL "pall"
#define PINT "pint"
#define POP "pop"
#define MALLOCERR "Error: malloc failed\n"
#define BG -8462315

#define ARGV_NUMB 2
#define BEGIN 0
#define NEXT 1
#define SPACE 32
#define PUSHERR 31
#define PALLERR 32
#define	PINTERR 34
#define POPERR 36
#define DEFAULTERR 0
#define NEWLINE '\n'

#define is_valide_fd(fd)((fd < 0) ? false : true)
#define is_op(op)((op == '-' || op == '+') ? true : false)

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct var_s - Structure representing variables.
 *
 * @line: A pointer to a string.
 * @ln: An integer variable.
 * @stack: A pointer to a stack structure.
 * @first: A boolean indicating if it is the first occurrence.
 */
typedef struct var_s
{
	char *line;
	int ln;
	stack_t *stack;
	bool first;
} var_t;

int     getFileDescriptorId(char *fileName);
void    saveFileInput(int fd);
size_t	ft_strlen(char *str);
int	ft_check_new_line(char *buffer);
char	*ft_strjoin(char *s1, char *s2);
char    *get_next_line(int fd);
char    **ft_split(char const *s, char c);
char    *ft_strdup(char *s);
int     ft_strcmp(const char *s1, const char *s2);
void    ft_free(char **src, char *line);
void    printError(char **opcode, var_t *data, int flag);
void	pall(stack_t *stack);
char    *newLineEraser(char *src);
void    stackFree(stack_t *stack);
bool    argChecker(char *str);
stack_t	*ft_malloc(void);
void	init(var_t *data);
bool	prePush(var_t *data, char **tmpOpcode);
void	pint(char **opcode, var_t *data);
void	pop(char **opcode, var_t *data);
#endif /*MONTY_H*/
