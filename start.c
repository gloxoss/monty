

#include "monty.h"

int status = 0;

/**
 * main - entry point
 * @argv: list of arguments passed to our program
 * @argc: amount of args
 *
 * Return: nothing
 */
int main(int argc, char **argv)
{
	FILE *file;
	size_t buf_len = 0;
	char *buffer = NULL;
	char *str = NULL;
	stack_t *stack = NULL;
	unsigned int line_cnt = 1;

	global.data_struct = 1;
	if (argc != 2)
		err_usg();

	file = fopen(argv[1], "r");

	if (!file)
		f_err(argv[1]);

	while ((getline(&buffer, &buf_len, file)) != (-1))
	{
		if (status)
			break;
		if (*buffer == '\n')
		{
			line_cnt++;
			continue;
		}
		str = strtok(buffer, " \t\n");
		if (!str || *str == '#')
		{
			line_cnt++;
			continue;
		}
		global.argument = strtok(NULL, " \t\n");
		opcode(&stack, str, line_cnt);
		line_cnt++;
	}
	free(buffer);
	free_stack(stack);
	fclose(file);
	exit(EXIT_SUCCESS);
}

/**
 * f_err - prints file error message and exits
 * @argv: argv given by main()
 *
 * Desc: print msg if  not possible to open the file
 * Return: nothing
 */
void f_err(char *argv)
{
	fprintf(stderr, "Error: Can't open file %s\n", argv);
	exit(EXIT_FAILURE);
}

/**
 * err_usg - prints usage message and exits
 *
 * Desc: if user does not give any file or more than
 * one argument to your program
 *
 * Return: nothing
 */
void err_usg(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}
