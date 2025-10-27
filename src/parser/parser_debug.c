#include "../../includes/minishell.h"

void	print_cmds(t_cmd *cmd)
{
	size_t	n;
	size_t	i;

	n = 0;
	while (cmd)
	{
		printf("CMD#%zu:", ++n);
		i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf(" argv[%zu]='%s'", i, cmd->argv[i]);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
}

