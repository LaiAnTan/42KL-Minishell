#include "../../headers/minishell.h"

int	builtin_echo(char **args)
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
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}