/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlai-an <tlai-an@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 10:31:55 by tlai-an           #+#    #+#             */
/*   Updated: 2023/06/19 14:12:28 by tlai-an          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	display_export_line(t_list *node)
{
	int		i;
	int		equal_pos;

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
	{
		write(1, node->env.str, ft_strlen(node->env.str));
		write(1, "\n", 1);
	}
}

static void	reset_printed(t_list *lst)
{
	t_list	*curr_node;

	curr_node = lst;
	while (curr_node != NULL)
	{
		curr_node->env.printed = 0;
		curr_node = curr_node->next;
	}
	return ;
}

// this doesnt crash and doesnt return 1 for no reason right
// right?
static int	print_asc_export(t_list *lst)
{
	int		lst_size;
	t_list	*curr_node;
	t_list	*smallest_node;

	lst_size = ft_lstsize(lst);
	reset_printed(lst);
	while (--lst_size >= 0)
	{
		curr_node = lst;
		smallest_node = lst;
		while (smallest_node->env.printed)
			smallest_node = smallest_node->next;
		while (curr_node != NULL)
		{
			if ((curr_node->env.str[0] < smallest_node->env.str[0])
				&& curr_node->env.printed == 0)
				smallest_node = curr_node;
			curr_node = curr_node->next;
		}
		smallest_node->env.printed = 1;
		display_export_line(smallest_node);
	}
	return (0);
}

static char	*get_var_name(char *str)
{
	int		i;
	int		j;
	char	*var_name;

	i = 0;
	j = 0;
	while (str[i] != '\0' && str[i] != '=')
		++i;
	var_name = (char *) malloc (sizeof(char) * (i + 1));
	while (j < i)
	{
		var_name[j] = str[j];
		j++;
	}
	var_name[j] = '\0';
	return (var_name);
}



int	builtin_export(char **args, t_data *data)
{
	int		i;
	char	*var_name;
	t_list	*node;

	i = 0;
	if (args[1] == NULL)
		return (print_asc_export(data->vars));
	while (args[++i] != NULL)
	{
		if (args[i][0] == '=')
			return (error_msg("export", args[i],
					"is not a valid identifier", 1));
		var_name = get_var_name(args[i]);
		node = find_var(data->vars, var_name);
		if (node == NULL)
			ft_lstadd_back(&data->vars, ft_lstnew_env(ft_strdup(args[i])));
		else
		{
			if (search_symbol(var_name, '=') == -1)
				continue ;
			free(node->env.str);
			node->env.str = ft_strdup(args[i]);
		}
		free(var_name);
	}
	return (0);
}
