#include "../headers/minishell.h"

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

void	ft_lstsort(t_list *lst)
{
	return;
}

void	display_export_line(t_list *node)
{
	int		i;
	int		equal_pos;

	i = 0;
	equal_pos = get_equal_pos(node);
	write(1, "declare -x ", 11);
	while (i <= equal_pos)
		write(1, &node->str[i++],1);
	write(1, "\"", 1);
	while (node->str[i] != '\0')
		write(1, &node->str[i++], 1);
	write(1, "\"\n", 2);
}

void	builtin_export(t_data *data, char **args)
{
	int		i;
	t_list	*lst;
	t_list	*head;

	i = 0;
	if (args == NULL)
	{
		lst = ft_lstcpy(data->vars);
		head = lst;
		// ft_lstsort(lst);
		while (lst != NULL)
		{
			display_export_line(lst);
			lst = lst->next;
		}
		lst = head;
		ft_lstfree(lst);
	}
	else
	{
		while (args[i] != NULL)
		{
			lst = data->vars;
			head = ft_lstnew(args[i]);
			ft_lstadd_back(&lst, head);
			i++;
		}
	}
}


void	builtin_env(t_data *data)
{
	ft_lstprint(data->vars);
}

void	builtin_exit(t_data *data)
{
	// free everything
	exit(0);
}