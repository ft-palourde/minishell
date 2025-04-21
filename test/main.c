#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("ptr = %p\n", pwd);
	printf("pwd = %s\n", pwd);
	free(pwd);
}