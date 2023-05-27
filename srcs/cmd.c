#include "../headers/minishell.h"

void	single_command(t_data *data, t_list *cmds)
{
	char	*cmd;
	char	**cmd_paths;

	cmd = ft_strdup(cmds->cmd.cmd[0]);
	cmd_paths = get_cmd_path(data, cmd);
	if (handle_builtins(cmd, cmds->cmd.cmd, data) == 0)
		exec_cmd(data, cmd_paths, cmds->cmd.cmd);
}

// why do we not have a command count
int		get_command_count(t_data *data)
{
	t_list	*counter;
	int		ret;

	ret = 0;
	counter = data->cmds;
	while (counter)
	{
		++ret;
		counter = counter->next;
	}
	return (ret);
}

void	multiple_commands(t_data *data)
{
	int	dispatched;
	int	cmd_count;
	// 0 - read 1 - write
	int	pipe_storage[2];
	int	prev_pipe;

	dispatched = 0;
	cmd_count = get_command_count(data);
	while (dispatched < cmd_count)
	{
		// when t_list have no init function
		data->cmds->in_fd = STDIN_FILENO;
		data->cmds->out_fd = STDOUT_FILENO;

		// piping
		if (!dispatched)
		{
			pipe(pipe_storage);
			data->cmds->out_fd = pipe_storage[1];
		}
		else if (dispatched == cmd_count - 1) // last command
		{
			data->cmds->in_fd = prev_pipe;
		}
		else // everything in between
		{
			data->cmds->in_fd = prev_pipe;
			pipe(pipe_storage);
			data->cmds->out_fd = pipe_storage[1];
		}

		if (!fork())
		{
			close(pipe_storage[0]);

			dup2(data->cmds->in_fd, STDIN_FILENO);
			dup2(data->cmds->out_fd, STDOUT_FILENO);

			single_command(data, data->cmds);
			// i fix this later
			exit(0);
		}
		else
		{
			// cleaning up file desc
			if (!dispatched)
			{
				close(pipe_storage[1]);
				prev_pipe = pipe_storage[0];
			}
			else if (dispatched == cmd_count - 1)
			{
				close(prev_pipe);
			}
			else
			{
				close(prev_pipe);
				close(pipe_storage[1]);
				prev_pipe = pipe_storage[0];
			}
			++dispatched;
			data->cmds = data->cmds->next;
		}
	}
	while (cmd_count)
	{
		// hey replace NULL with the saved exit code thanks
		waitpid(0, NULL, 0);
		--cmd_count;
	}
}

void	run_cmd(t_data *data)
{
	if (data->cmds->next)
		multiple_commands(data);
	else
		single_command(data, data->cmds);
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
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				if (execve(cmd_paths[i], args, data->my_envp) == -1)
				{
					free_2d_array(&cmd_paths);
					free_2d_array(&args);
					return (0);
				}
			}
			else
			{
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
				waitpid(-1, NULL, 0);
				return (0);
			}
		}
		i++;
	}
	return (0);
}