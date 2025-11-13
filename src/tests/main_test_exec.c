#include "../../includes/minishell.h"

// MAIN PARA PROBAR LA EJECUCIÓN DIRECTA DE LOS COMANDOS
/*
int main(void)
{
    t_cmd cmd;
    char *args[] = {"ls", "-la", NULL};

    cmd.argv = args;
    cmd.next = NULL;

    printf("Probando ejecución directa de 'ls -la'...\n");
    execute_command(&cmd, environ);

    printf("Comando ejecutado correctamente ✅\n");
    return (0);
}*/

// MAIN PARA PROBAR LA EJECUCIÓN DE LOS COMANDOS
/*
int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	if (argc < 2)
	{
		printf("Uso: ./minishell comando\n");
		return (1);
	}
	cmd.argv = &argv[1];
	cmd.infile = STDIN_FILENO;
	cmd.outfile = STDOUT_FILENO;
	cmd.is_builtin = 0;
	cmd.next = NULL;
	return (execute_command(&cmd, envp));
}
*/