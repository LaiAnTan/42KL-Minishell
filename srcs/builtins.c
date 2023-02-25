#include "../headers/minishell.h"

/*
builtin commands

*	echo with option -n
*	cd with only a relative or absolute path
*	pwd with no options
*	export with no options
*	unset with no options
*	env with no options or arguments
*	exit with no options

*/

int	handle_builtins(int argc, char **args, t_data *data)
{
	if (!args || !*args)
		return (0);
	if (ft_strcmp(args[0], "echo"))
		builtin_echo(argc, args, data);
	else if (ft_strcmp(args[0], "cd"))
		builtin_cd(argc, args, data);
	else if (ft_strcmp(args[0], "pwd"))
		builtin_pwd(argc, args, data);
	else if (ft_strcmp(args[0], "export"))
		builtin_export(argc, args, data);
	else if (ft_strcmp(args[0], "unset"))
		builtin_unset(argc, args, data);
	else if (ft_strcmp(args[0], "env"))
		builtin_env(argc, args, data);
	else if (ft_strcmp(args[0], "exit"))
		builtin_exit(argc, args, data);
	else
		printf("command not found");
	return (0);
}

void builtin_echo(int argc, char **args, t_data *data)
{
	int		i;
	int		nl;

	i = 2;
	nl = 0;
	if (ft_strcmp(args[1], "-n"))
		nl = 1;
	while (i < argc)
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return ;
}

void builtin_cd(int argc, char **args, t_data *data)
{

}

void builtin_pwd(int argc, char **args, t_data *data)
{
	
}

void display_export_line(t_list *node)
{
	int i;
	int equal_pos;

	i = 0;
	equal_pos = get_equal_pos(node);
	write(1, "declare -x ", 11);
	if (equal_pos != -1)
	{
		while (i <= equal_pos)
			write(1, &node->str[i++], 1);
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
	int		lst_size;
	t_list	*curr_node;
	t_list	*smallest_node;

	lst_size = ft_lstsize(lst);
	curr_node = lst;
	while (curr_node != NULL)
	{
		curr_node->printed = 0;
		curr_node = curr_node->next;
	}
	while (lst_size > 0)
	{
		curr_node = lst;
		smallest_node = lst;
		while (smallest_node->printed)
			smallest_node = smallest_node->next;
		while (curr_node != NULL)
		{
			if ((curr_node->str[0] < smallest_node->str[0]) && curr_node->printed == 0)
				smallest_node = curr_node;
			curr_node = curr_node->next;
		}
		smallest_node->printed = 1;
		display_export_line(smallest_node);
		lst_size--;
	}
}

void builtin_export(int argc, char **args, t_data *data)
{
	int i;
	t_list *lst;
	t_list *head;

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

void builtin_unset(int argc, char **args, t_data *data)
{
	int i;

	i = 0;
	if (args == NULL)
		return;
	else
	{
		while (args[i] != NULL)
		{
			// ft_lstdel();
			i++;
		}
	}
}

void builtin_env(int argc, char **args, t_data *data)
{
	ft_lstprint(data->vars);
}

void builtin_exit(int argc, char **args, t_data *data)
{
	// free everything
	exit(0);
}