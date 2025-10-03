#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
    char *line;

    while (1)
    {
        line = readline("minishell$ ");
        if (!line) // Ctrl-D
        {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);

        // TODO: pasar 'line' al tokenizador / parser
        free(line);
    }
    return 0;
}
