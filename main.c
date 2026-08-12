#include "shell.h"

/**
 * prompt - Displays the shell prompt if in interactive mode
 *
 * Return: Nothing.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);
}

/**
 * execute_cmd - Executes a command using fork and execve
 * @args: Array of string arguments
 * @prog_name: Name of the program executable (argv[0])
 *
 * Return: Nothing.
 */
void execute_cmd(char **args, char *prog_name)
{
	pid_t child_pid;
	int status;

	if (args == NULL || args[0] == NULL)
		return;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return;
	}

	if (child_pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			fprintf(stderr, "%s: 1: %s: not found\n", prog_name, args[0]);
			exit(127);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Entry point for the simple shell
 * @ac: Argument count (unused)
 * @av: Argument vector
 *
 * Return: Always 0 on success.
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;
	(void)ac;

	while (1)
	{
		prompt();
		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		args = parse_line(line);
		if (args != NULL && args[0] != NULL)
			execute_cmd(args, av[0]);

		free(args);
	}

	free(line);
	return (0);
}
