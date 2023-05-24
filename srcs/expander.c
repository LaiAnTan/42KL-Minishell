#include "../headers/minishell.h"

char	*find_var(t_data *data, char *name)
{
	t_list	*lst;

	lst = data->vars;
	while (lst)
	{
		if (ft_strcmp_equals(lst->env.str, name) == 0)
			return(get_val(lst));
		lst = lst->next;
	}
	return (NULL);
}

void	handle_dollar(t_data *data, char ***new, int *dollar_pos)
{
	char	*val;

	if (data->tokens[*dollar_pos] == NULL)
		return ;
	if (ft_strcmp(data->tokens[*dollar_pos], "$") == 0)
	{
		dollar_pos++;
		if (data->tokens[*dollar_pos] != NULL)
		{
			val = find_var(data, data->tokens[*dollar_pos]);
			dollar_pos++;
			if (val == NULL)
				return ;
			*new = realloc_append(*new, val);
			free(val);
		}
	}
	else
		*new = realloc_append(*new, data->tokens[*dollar_pos]);
}

int	count_double(char **e)
{
	int	i = 0;

	while (e[i])
		++i;
	return (i);
}

// ? trying to fix this now
int	expander(t_data *data)
{
	int		i;
	char	**new;
	int		tokencount = count_double(data->tokens);

	i = 0;
	new = malloc (sizeof(char *));
	new[0] = NULL;
	if (!data || !data->tokens)
		return (0);
	while (i < tokencount)
	{
		if (ft_strcmp(data->tokens[i], "\'") == 0)
		{
			i++;
			while (data->tokens[i] != NULL && ft_strcmp(data->tokens[i], "\'") != 0)
			{
				new = realloc_append(new, data->tokens[i]);
				i++;
			}
		}
		else if (ft_strcmp(data->tokens[i], "\"") == 0)
		{
			i++;
			while (data->tokens[i] != NULL && ft_strcmp(data->tokens[i], "\"") != 0)
			{
				handle_dollar(data, &new, &i);
				i++;
			}
		}
		else
		{
			handle_dollar(data, &new, &i);
			i++;
		}
	}
	free_2d_array(&data->tokens);
	data->tokens = new;
	return (1);
}