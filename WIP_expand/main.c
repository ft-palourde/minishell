#include "expand_test.h"

int	main(int argc, char **argv, char **envp)
{
	char *str;
	char	*exp;

	str = "toto$TOTO$TOTO";
	(void) argc;
	exp = expand_chunk(argv[1], envp);
	printf("%s\n", exp);
	return (0);
}
