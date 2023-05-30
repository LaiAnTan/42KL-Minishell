#include "../../headers/minishell.h"

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
	if (i == ft_strlen(str)) //failsafe
		return (NULL);
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
		data->last_exit = 0;
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
				printf("variable found, %s\n", node->env.str);
				free(node->env.str);
				node->env.str = ft_strdup(args[i]);
			}
		}
		i++;
	}
}