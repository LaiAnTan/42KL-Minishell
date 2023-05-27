#include "../headers/minishell.h"

int	*get_next_redirect_info(char **args, int start_index)
{
	int		i;
	int		*info;

	i = start_index;
	info = (int *) malloc (sizeof(int) * 2);
	info[0] = 0;
	info[1] = 0;
	while (args[i] != NULL)
	{
		if (info[0] != 0)
			return (info);
		info[1] = i;
		if (ft_strcmp(args[i], ">") == 0)
			info[0] = 1;
		else if (ft_strcmp(args[i], "<") == 0)
			info[0] = 2; 
		else if (ft_strcmp(args[i], ">>") == 0)
			info[0] = 3;
		else if (ft_strcmp(args[i], "<<") == 0)
			info[0] = 4;
		i++;
	}
	return (NULL);
}

char	**get_new_args(char **args)
{	
	int		i;
	int		*redir_info;
	char	**new;

	i = 0;
	redir_info = get_next_redirect_info(args, 0);
	if (redir_info == NULL)
		return (NULL);
	new = (char **) malloc (sizeof(char *) * redir_info[1]);
	while (args[i] < redir_info[1])
	{
		new[i] = ft_strdup(args[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	handle_redirect(char **args, t_data *data)
{
	int		i;
	int		fd;
	int		*redir_info; // 0 = type, 1 = index
	char	**new_args;

	i = 0;
	new_args = get_new_args(args);
	if (new_args == NULL)
		return (0);
	if (count_2d_array(args) == redir_info[1])
		return (-1);
	while (args[i] != NULL)
	{
		redir_info = get_next_redirect_info(args, i);
		if (redir_info == NULL) // no more redirects
			return (1);
		fd = open(args[redir_info[1] + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	}
}