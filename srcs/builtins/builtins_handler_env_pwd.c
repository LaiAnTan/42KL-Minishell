#include "../../headers/minishell.h"

void	builtin_pwd(t_data *data)
{
	write(1, data->cwd, ft_strlen(data->cwd));
	write(1, "\n", 1);
}

void builtin_env(t_data *data)
{
	ft_lstprint_env(data->vars);
}

int	handle_builtins(char *cmd, char **args, t_data *data)
{
	if (!args || !*args)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(args, data);
	else if (ft_strcmp(cmd, "cd") == 0)
		builtin_cd(args, data);
	else if (ft_strcmp(cmd, "pwd") == 0)
		builtin_pwd(data);
	else if (ft_strcmp(cmd, "export") == 0)
		builtin_export(args, data);
	else if (ft_strcmp(cmd, "unset") == 0)
		builtin_unset(args, data);
	else if (ft_strcmp(cmd, "env") == 0)
		builtin_env(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit(args, data);
	else
		return (0);
	return (1);
}