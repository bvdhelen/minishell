#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <readline/readline.h>
//#include <readline/history.h>

/* int	main(void)
{
	char	*rl;

	rl = readline(":-) ");
	printf("%s\n", rl);
	free(rl);
	return (0);
} */

int	main(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	chdir("/home/danielji/Documents/philosophers");
	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}