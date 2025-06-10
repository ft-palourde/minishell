#include "expand_test.h"

int	main(int argc, char **argv, char **envp)
{
	char	*exp;

	(void) argc;
	exp = str_expand(argv[1], envp);
	printf("%s\n", exp);
	return (0);
}
