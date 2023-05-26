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

void	builtin_echo(char **args, t_data *data)
{
	int		i;
	int		nl;

	i = 1;
	nl = 0;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		nl = 1;
		i = 2;
	}
	while (args[i] != NULL)
	{
		write(1, args[i], ft_strlen(args[i]));
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return ;
}

void	builtin_cd(char **args, t_data *data)
{
	// chdir();


}

void	builtin_pwd(char **args, t_data *data)
{
	write(1, data->cwd, ft_strlen(data->cwd));
	write(1, "\n", 1);
}

void	display_export_line(t_list *node)
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

void	print_asc_export(t_list *lst)
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

int	valid_assign(char *str)
{
	if (str == NULL || *str == '=')
		return (0);
	str++;
	while (*str != '\0')
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}


char	*get_var_name(char *str)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	j = 0;
	while (str[i] != '=')
		i++;
	var_name = (char *) malloc (sizeof(char) * (i + 1));
	while (j < i)
	{
		var_name[j] = str[j];
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}

void	builtin_export(char **args, t_data *data)
{
	int i;
	char	*var_name;
	t_list	*lst;
	t_list	*node;

	i = 1;
	lst = data->vars;
	if (args[1] == NULL)
	{
		print_asc_export(lst);
		return ;
	}
	while (args[i] != NULL)
	{
		if (valid_assign(args[i]) == 1)
		{
			var_name = get_var_name(args[i]);
			node = find_var(lst, var_name);
			free(var_name);
			if (node == NULL)
			{
				printf("variable not found\n");
				node = ft_lstnew_env(ft_strdup(args[i]));
				ft_lstadd_back(&lst, node);
			}
			else
			{
				printf("variable found\n");
				free(node->env.str);
				node->env.str = ft_strdup(args[i]);
			}
		}
		i++;
	}
}

void builtin_unset(char **args, t_data *data)
{
	int i;

	i = 0;
	while (args[i] != NULL)
	{
		// find name too
		// ft_lstdel();
		i++;
	}
}

void builtin_env(t_data *data)
{
	ft_lstprint_env(data->vars);
}

void builtin_exit(char **args, t_data *data)
{
	int		size;
	int		exit_code;

	if (count_2d_array(args) > 2)
		printf("exit: too many arguements\n");
	if (args[1] == NULL)
		exit_code = 0;
	else if (is_numeric(args[1]) == 1)
		exit_code = ft_atoi(args[1]);
	else
		exit_code = 2;
	while (exit_code >= 256) // overflow protection
		exit_code = exit_code - 256;
	// remember to free stuff here
	exit(exit_code);
}

int	handle_builtins(char *cmd, char **args, t_data *data)
{
	if (!args || !*args)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0)
		builtin_echo(args, data);
	else if (ft_strcmp(cmd, "cd") == 0)
		builtin_cd(args, data);
	else if (ft_strcmp(cmd, "pwd") == 0)
		builtin_pwd(args, data);
	else if (ft_strcmp(cmd, "export") == 0)
		builtin_export(args, data);
	else if (ft_strcmp(cmd, "unset") == 0)
		builtin_unset(args, data);
	else if (ft_strcmp(cmd, "env") == 0)
		builtin_env(data);
	else if (ft_strcmp(cmd, "exit") == 0)
		builtin_exit(args, data);
	else
		return (0);
	return (1);
}