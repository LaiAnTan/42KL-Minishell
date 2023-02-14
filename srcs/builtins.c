#include "minishell.h"

/*
builtin commands

*	echo with option -n
*	cd with only a relative or absolute path
*	pwd with no options
!	export with no options
!	unset with no options
*	env with no options or arguments
*	exit with no options

*/

void	builtin_echo(char *str, char option)
{
	write(STDOUT_FILENO, str, ft_strlen(str));	
	if (option = 'n')
		write (STDOUT_FILENO, "\n", 1);
}

void	builtin_cd(char *path, char type)
{
	if (type = 'a')
	{

	}
	if (type = 'r')
	{

	}
}

void	builtin_pwd(t_data *data)
{
	write(STDOUT_FILENO, data->curr_path, ft_strlen(data->curr_path));
}

void	builtin_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
}

void	builtin_exit(t_data *data)
{
	// free everything
	exit(0);
}