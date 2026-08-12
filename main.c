#include "shell.h"

/**
 * prompt - Affiche le prompt si le shell est en mode interactif
 */
void prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "($) ", 4);
}

/**
 * execute_cmd - Exécute une commande donnée en argument
 * @args: Tableau d'arguments (ex: {"/bin/ls", NULL})
 * @prog_name: Nom du programme principal (argv[0])
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
 * main - Point d'entrée principal du simple shell
 * @ac: Nombre d'arguments
 * @av: Tableau des arguments
 *
 * Return: Toujours 0
 */
int main(int ac, char **av)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[2];
	(void)ac;

	while (1)
	{
		prompt();
		nread = getline(&line, &len, stdin);

		/* Gestion de EOF (Ctrl+D) */
		if (nread == -1)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(0);
		}

		/* Supprimer le saut de ligne \n en fin de chaîne */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* Ignorer les lignes vides */
		if (line[0] == '\0')
			continue;

		args[0] = line;
		args[1] = NULL;

		execute_cmd(args, av[0]);
	}

	free(line);
	return (0);
}
