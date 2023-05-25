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

void builtin_echo(char **args, t_data *data)
{
	int		i;
	int		nl;

	i = 2;
	nl = 0;
	if (ft_strcmp(args[1], "-n"))
		nl = 1;
	while (args[i] != NULL)
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return ;
}

void builtin_cd(char **args, t_data *data)
{
	char	buf_path[PATH_MAX];
	
}

void builtin_pwd(char **args, t_data *data)
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
			write(1, &node->env.str[i++], 1);
		write(1, "\"", 1);
		while (node->env.str[i] != '\0')
			write(1, &node->env.str[i++], 1);
		write(1, "\"\n", 2);
	}
	else
		write(1, node->env.str, ft_strlen(node->env.str));
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
		curr_node->env.printed = 0;
		curr_node = curr_node->next;
	}
	while (lst_size > 0)
	{
		curr_node = lst;
		smallest_node = lst;
		while (smallest_node->env.printed)
			smallest_node = smallest_node->next;
		while (curr_node != NULL)
		{
			if ((curr_node->env.str[0] < smallest_node->env.str[0]) && curr_node->env.printed == 0)
				smallest_node = curr_node;
			curr_node = curr_node->next;
		}
		smallest_node->env.printed = 1;
		display_export_line(smallest_node);
		lst_size--;
	}
}

void builtin_export(char **args, t_data *data)
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
			head = ft_lstnew_env(args[i]);
			ft_lstadd_back(&lst, head);
			i++;
		}
	}
}

void builtin_unset(char **args, t_data *data)
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

void builtin_env(t_data *data)
{
	ft_lstprint(data->vars);
}

void builtin_exit(char **args, t_data *data)
{
	int		size;
	int		exit_code;

	size = count_double(args);
	if (size > 2);
		exit_code = 2;
	if (is_numeric(args[1]) == 1)
		exit_code = ft_atoi(args[1]); // need to make atoi
	// free stuff here
	exit(exit_code);
}

int	handle_builtins(char **args, t_data *data)
{
	if (!args || !*args)
		return (0);
	if (ft_strcmp(args[0], "echo"))
		builtin_echo(args, data);
	else if (ft_strcmp(args[0], "cd"))
		builtin_cd(args, data);
	else if (ft_strcmp(args[0], "pwd"))
		builtin_pwd(args, data);
	else if (ft_strcmp(args[0], "export"))
		builtin_export(args, data);
	else if (ft_strcmp(args[0], "unset"))
		builtin_unset(args, data);
	else if (ft_strcmp(args[0], "env"))
		builtin_env(data);
	else if (ft_strcmp(args[0], "exit"))
		builtin_exit(args, data);
	else
		printf("command not found");
	return (0);
}