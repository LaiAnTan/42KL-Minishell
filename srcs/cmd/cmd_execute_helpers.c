#include "../../headers/minishell.h"

void	exec_child(char *cmd_path, char **args, char **my_envp)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (execve(cmd_path, args, my_envp) == -1)
		exit(errno);
}

int	exec_parent(t_data *data, int pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	return (get_exit_code(data, status));
}