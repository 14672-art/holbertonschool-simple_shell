#include "shell.h"

/**
 * parse_line - Tokenizes an input string into an array of arguments
 * @line: Line string read from stdin
 *
 * Return: Pointer to NULL-terminated array of argument strings
 */
char **parse_line(char *line)
{
	int bufsize = 1024, i = 0;
	char **tokens;
	char *token;

	tokens = malloc(bufsize * sizeof(char *));
	if (!tokens)
		return (NULL);

	token = strtok(line, DELIM);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, DELIM);
	}
	tokens[i] = NULL;
	return (tokens);
}
