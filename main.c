#include "header.h"

/**
 * main(:)? (- shell)?
 * @ac : number of argement.
 * @av: list of argements.
 * @env : lists of the envirement variables.
 * Return: 0
 */
int main(__attribute__ ((unused)) int ac, char **av, char **env)
{
	char *buffer = NULL;
	size_t bufsize = 0;
	int word = 0, characters = 0, test = 0;
	his *head = NULL;
	struct stat st;

	while (1)
	{
		signal(SIGINT, csignal);
		if (isatty(STDIN_FILENO))
			_print("#cisfun$ ");
		characters = getline(&buffer, &bufsize, stdin);
		if (characters == -1)
			break;
		if (history(buffer, &head) == 0)
			continue;
		buffer[characters - 1] = '\0';
		word = words(buffer, ';');
		if (word != 0)
		{
			test = magic(buffer, word, &head, env, av);
			if (test == 1)
				return (0);
			if (test == 2)
				continue;
			if (test == 99)
			{
				if (stat("ls;", &st) == 0)
					perror(av[0]);
				exit(2);
			}
		}

	}
	free_all(buffer, &head, env);
	return (0);
}