#include "shell.h"

/**
 * prompt - Displays prompt if shell is in interactive mode
 *
 * Return: Nothing.
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * execute_cmd - Executes a single command using fork and execve
 * @cmd: Command path string
 * @prog_name: Name of the shell executable (argv[0])
 *
 * Return: Nothing.
 */
void execute_cmd(char *cmd, char *prog_name)
{
	pid_t child_pid;
	int status;
	char *args[2];

	args[0] = cmd;
	args[1] = NULL;

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
			perror(prog_name);
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}
}

/**
 * main - Entry point for simple_shell
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

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		execute_cmd(line, av[0]);
	}

	free(line);
	return (0);
}
