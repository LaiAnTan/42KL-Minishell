#include "../../headers/minishell.h"

void builtin_exit(char **args, t_data *data)
{
	int		size;
	int		exit_code;

	if (count_2d_array(args) > 2)
	{
		printf("exit: too many arguements\n");
		return ;
	}
	if (args[1] == NULL)
		exit_code = 0;
	else if (is_numeric(args[1]) == 1)
		exit_code = ft_atoi(args[1]);
	else
		exit_code = 2;
	while (exit_code >= 256) // overflow protection
		exit_code = exit_code - 256;
	printf("process exited with code %d\n", exit_code); // ok apparently exit auto frees
	exit(exit_code);
}