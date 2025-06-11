#include "expand_test.h"

int	main(int argc, char **argv, char **envp)
{
	char	*exp;
	char	*str = "abc\"$TOTO\"'$TOTO'$TOTO\"$TOTO\"";

	(void) argv;
	(void) argc;
	exp = str_expand(str, envp);
	printf("%s\n", exp);
	free(exp);
	return (0);
}
