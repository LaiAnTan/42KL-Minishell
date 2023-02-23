#include "../headers/minishell.h"

int init_data(t_data *data, char **envp)
{
	data->vars = set_env(envp);
	return (1);
}