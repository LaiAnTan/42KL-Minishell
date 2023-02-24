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
	if (equal_pos != -1)
	{
		while (i <= equal_pos)
			write(1, &node->str[i++],1);
		write(1, "\"", 1);
		while (node->str[i] != '\0')
			write(1, &node->str[i++], 1);
		write(1, "\"\n", 2);
	}
	else
		write(1, node->str, ft_strlen(node->str));
}

void print_asc_export(t_list *lst)
{
	int lst_size;
	t_list *head;
	t_list *node;

	head = lst;
	node = lst;
	lst_size = ft_lstsize(lst);
	printf("lst size = %d\n", lst_size);
	while (lst_size)
	{
		node = head;
		lst = head;
		while (lst != NULL)
		{
			if (lst->str[0] < node->str[0] && lst->printed == 0)
				node = lst;
			lst = lst->next;
		}
		display_export_line(node);
		node->printed = 1;
		lst_size--;

	}
	lst = head;
	while (lst != NULL)
	{
		lst->printed = 0;
		lst = lst->next;
	}
}

void	builtin_export(t_data *data, char **args)
{
	int		i;
	t_list	*lst;
	t_list	*head;

	i = 0;
	lst = data->vars;
	if (args == NULL)
		print_asc_export(lst);
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

void	builtin_unset(t_data *data, char **args)
{
	int		i;

	i = 0;
	if (args == NULL)
		return ;
	else
	{
		while (args[i] != NULL)
		{
			//ft_lstdel();
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