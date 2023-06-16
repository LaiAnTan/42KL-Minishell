#include "../../headers/minishell.h"

static void	in_child(int last_var, t_data *data, t_list *curr, int to_close)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!(last_var))
		close(to_close);
	if (handle_redirect(curr->cmd.cmd, curr, data->stdin_backup) == -1)
		exit (1);
	curr->cmd.cmd = get_cmd_args_without_redirect(curr->cmd.cmd);
	dup2(curr->in_fd, STDIN_FILENO);
	dup2(curr->out_fd, STDOUT_FILENO);
	exit (single_command(data, curr));
}

static void	wait_all_commands(int cmd_count, int last_child_pid, t_data *data)
{
	int	status;

	while (cmd_count)
	{
		waitpid(last_child_pid, &status, 0);
		if (last_child_pid)
			get_exit_code(data, status);
		last_child_pid = 0;
		--cmd_count;
	}
}

static void	do_pumbling(int dispatched, int cmd_count, int *pipe_storage, int prev_pipe, t_list *cur)
{
	if (dispatched != cmd_count - 1)
	{
		pipe(pipe_storage);
		cur->out_fd = pipe_storage[1];
	}
	if (dispatched)
		cur->in_fd = prev_pipe;
}

static void	clean_pipes(int dispatched, int cmd_count, 
	int *pipe_storage, int *prev_pipe)
{
	if (dispatched)	
		close((*prev_pipe));
	if (dispatched != cmd_count - 1)
	{
		close(pipe_storage[1]);
		(*prev_pipe) = pipe_storage[0];
	}
}

void	multiple_commands(t_data *data)
{
	t_list	*curr;
	int		disptch;
	int		cmd_c;
	int		pipe_storage[3];
	int		last_child_pid;

	disptch = 0;
	cmd_c = get_command_count(data);
	curr = data->cmds;
	while (disptch < cmd_c)
	{
		do_pumbling(disptch, cmd_c, &pipe_storage[0], pipe_storage[2], curr);
		last_child_pid = fork();
		if (last_child_pid == 0)
			in_child((disptch == cmd_c - 1), data, curr, pipe_storage[0]);
		else
		{
			clean_pipes(disptch, cmd_c, &pipe_storage[0], &pipe_storage[2]);
			++disptch;
			curr = curr->next;
		}
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait_all_commands(cmd_c, last_child_pid, data);
}