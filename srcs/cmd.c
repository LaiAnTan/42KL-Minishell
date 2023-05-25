#include "../headers/minishell.h"

void	run_cmd(t_data *data)
{
	char	*cmd;
	char	**cmd_paths;

	cmd = ft_strdup(data->cmds->cmd.cmd[0]);
	cmd_paths = get_cmd_path(data, cmd);
	if (handle_builtins(cmd, data->cmds->cmd.cmd, data) == 0)
		exec_cmd(data, cmd_paths, data->cmds->cmd.cmd);
}

int	exec_cmd(t_data *data, char **cmd_paths, char **args)
{
	int		i;
	int		status;

	i = 0;
	rebuild_envp(data);
	while (cmd_paths[i] != NULL)
	{
		if (args[0] != NULL)
			free(args[0]);
		args[0] = ft_strdup(cmd_paths[i]);
		status = access(args[0], X_OK);
		if (!status)
		{
			if (!fork())
			{
				if (execve(cmd_paths[i], args, data->my_envp) == -1)
				{
					free_2d_array(&cmd_paths);
					free_2d_array(&args);
					return (0);
				}
			}
			else
			{
				waitpid(-1, NULL, 0);
				return (0);
			}
		}
		i++;
	}
	return (0);
}