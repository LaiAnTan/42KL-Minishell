#include "../../headers/minishell.h"

int builtin_exit(char **args, t_data *data)
{
	int		size;
	int		exit_code;

	if (count_2d_array(args) > 2)
	{
		printf("exit: too many arguements\n");
		return (1);
	}
	else if (!is_numeric(args[1]))
	{
		printf("exit: %s: numeric arguement required", args[1]);
		exit_code = 2;
	}
	else if (args[1] == NULL)
		exit_code = 0;
	else
		exit_code = ft_atoi(args[1]);
	while (exit_code >= 256) // overflow protection
		exit_code = exit_code - 256;
	printf("process exited with code %d\n", exit_code); // ok apparently exit auto frees
	// im not sure if exit auto frees but fsan didnt complain sOOOOO
	exit(exit_code);
	// whoops
	return (exit_code);
}