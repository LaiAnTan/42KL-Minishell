#include "../../headers/minishell.h"

void	builtin_echo(char **args, t_data *data)
{
	int		i;
	int		nl;

	i = 1;
	nl = 1;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		nl = 0;
		i = 2;
	}
	while (args[i] != NULL)
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	data->last_exit = 0;
	return ;
}