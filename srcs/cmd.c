#include "../headers/minishell.h"

int	single_command(t_data *data, t_list *cmds)
{
	int		exit_status;
	char	*cmd;
	char	**cmd_paths;

	cmd = ft_strdup(cmds->cmd.cmd[0]);
	cmd_paths = get_cmd_path(data, cmd);
	exit_status = handle_builtins(cmd, cmds->cmd.cmd, data);
	if (exit_status == -1)
		return (exec_cmd(data, cmd_paths, cmds->cmd.cmd));
	else
		data->last_exit = exit_status;
	// this will only return if the built-in was ran
	return (69);
}

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

void	get_exit_code(t_data *data, int exit_status)
{
	if (WIFEXITED(exit_status))
		data->last_exit = WEXITSTATUS(exit_status);
	else
		if (WIFSIGNALED(exit_status))
			data->last_exit = 130;
}

void	multiple_commands(t_data *data)
{
	int	dispatched;
	int	cmd_count;
	// 0 - read 1 - write
	int	pipe_storage[2];
	int	prev_pipe;
	int	status;

	// uhoh
	int	last_child_pid;

	dispatched = 0; // number of commands that have been forked and ran
	cmd_count = get_command_count(data);
	while (dispatched < cmd_count)
	{
		// piping & setup fd
		if (!dispatched) // first
		{
			pipe(pipe_storage);
			data->cmds->out_fd = pipe_storage[1]; // command output is pipe input
		}
		else if (dispatched == cmd_count - 1) // last command
		{
			data->cmds->in_fd = prev_pipe; // command input is previous output
		}
		else // everything in between
		{
			data->cmds->in_fd = prev_pipe; // command input is previous output
			pipe(pipe_storage);
			data->cmds->out_fd = pipe_storage[1]; // command output is pipe input
		}

		// forking
		last_child_pid = fork();
		if (last_child_pid == 0) // child redirect input and output
		{
			close(pipe_storage[0]);
			if (handle_redirect(data->cmds->cmd.cmd, &data->cmds->in_fd, &data->cmds->out_fd) == -1)
				printf("error happened\n");
			data->cmds->cmd.cmd = get_cmd_args_without_redirect(data->cmds->cmd.cmd);

			dup2(data->cmds->in_fd, STDIN_FILENO);
			dup2(data->cmds->out_fd, STDOUT_FILENO);

			exit (single_command(data, data->cmds));
		}
		else // parent cleans up fd
		{
			if (!dispatched) // first
			{
				close(pipe_storage[1]);
				prev_pipe = pipe_storage[0];
			}
			else if (dispatched == cmd_count - 1) // last
			{
				close(prev_pipe);
			}
			else // between
			{
				close(prev_pipe);
				close(pipe_storage[1]);
				prev_pipe = pipe_storage[0];
			}

			// move to next command
			++dispatched;
			data->cmds = data->cmds->next;
		}
	}
	while (cmd_count) // wait for all processes
	{
		waitpid(last_child_pid, &status, 0);
		if (last_child_pid)
			get_exit_code(data, status);
		last_child_pid = 0; // wait for all of the other processes
		--cmd_count;
	}
}

void	run_cmd(t_data *data)
{
	if (data->cmds->next)
		multiple_commands(data);
	else
	{
		if (handle_redirect(data->cmds->cmd.cmd, &data->cmds->in_fd, &data->cmds->out_fd) == -1)
			printf("error happened\n");
		data->cmds->cmd.cmd = get_cmd_args_without_redirect(data->cmds->cmd.cmd);
		single_command(data, data->cmds);
	}
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
				waitpid(-1, &status, 0);
				get_exit_code(data, status);
				return (0);
			}
		}
		i++;
	}
	printf("%s: command not found\n", args[0]); // need to remove path here
	return (127);
}