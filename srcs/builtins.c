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
	char	*buf_path;


}

void builtin_pwd(char **args, t_data *data)
{
	printf("%s", data->cwd);
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
	if (args[1] == NULL)
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
	while (args[i] != NULL)
	{
		// ft_lstdel();
		i++;
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

	if (count_double(args) > 2)
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

char	*strip_cmd_path(char *cmd_path)
{
	int		i;
	int		j;
	int		len;
	char	*cmd;

	len = ft_strlen(cmd_path);
	i = len;
	j = 0;
	while (cmd_path[i - 1] != '/')
		--i;
	cmd = (char *) malloc (sizeof(char) * (len - i + 1));
	while (i <= len)
	{
		cmd[j] = cmd_path[i];
		i++;
		j++;
	}
	cmd[j] == '\0';
	return (cmd);
}

int	handle_builtins(char **args, t_data *data) // args[0] is with path
{
	char	*cmd;

	if (!args || !*args)
		return (0);
	cmd = strip_cmd_path(args[0]); // strip to get cmd name only
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
		printf("command not found\n");
	return (0);
}