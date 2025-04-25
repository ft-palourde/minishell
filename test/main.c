#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int ac, char **av, char **env)
{
	for (int i = 0; i < ac; i++)
		printf("arg[%d] = %s\n", i, av[i]);
	execve((const char *)av[1], &av[1], env);
	return (0);
}
