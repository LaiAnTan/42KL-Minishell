#include "../headers/minishell.h"

void	free_2d_arrays(char **a, char **b)
{
	int		i;

	i = 0;
	while (a[i])
		free(a[i++]);
	i = 0;
	while (b[i])
		free(b[i++]);
	free(a);
	free(b);
}

void	run_cmd(t_data *data, char *cmd_with_params)
{
	char	*cmd;
	char	**args;
	char	**cmd_paths;

	args = ft_split(cmd_with_params, ' ');
	cmd = ft_strdup(args[0]);
	cmd_paths = get_cmd_path(data, cmd);
	exec_cmd(data, cmd, cmd_paths, args);
}

int	exec_cmd(t_data *data, char *cmd, char **cmd_paths, char **args)
{
	int		i;
	int		status;

	i = 0;
	rebuild_envp(data);
	while (cmd_paths[i])
	{
		if (args[0])
			free(args[0]);
		args[0] = ft_strdup(cmd_paths[i]);
		status = access(args[0], X_OK);
		if (!status)
		{
			if (execve(cmd_paths[i], args, data->my_envp) == -1)
			{
				free_2d_arrays(cmd_paths, args);
				//failed
				return (0);
			}
		}
		else
			i++;
	}
	free_2d_arrays(cmd_paths, args);
	//failed
	return (0);
}