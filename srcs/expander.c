#include "../headers/minishell.h"

char	*find_var(t_data *data, char *name)
{
	int		pos;
	char	*val;
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

void	handle_dollar(t_data *data, char ***new, int dollar_pos)
{
	char	*val;

	if (data->tokens[dollar_pos + 1] != NULL)
	{
		val = find_var(data, data->tokens[dollar_pos + 1]);
		if (val != NULL)
			*new = realloc_append(*new, val);
		free(val);
	}
}

int	expander(t_data *data)
{
	int		i;
	char	*expanded;
	char	**new;

	i = 0;
	expanded = NULL;
	new[0] = NULL;
	while (data->tokens[i] != NULL)
	{
		if(ft_strcmp(data->tokens[i], "\'") == 0)
		{
			while (ft_strcmp(data->tokens[++i], "\'") != 0)
				new = realloc_append(new, data->tokens[i]);
		}
		else if (ft_strcmp(data->tokens[i], "\"") == 0)
		{
			while (ft_strcmp(data->tokens[++i], "\"") != 0)
			{
				if (ft_strcmp(data->tokens[i], "$") == 0)
					handle_dollar(data, &new, i);
				else
					new = realloc_append(new, data->tokens[i]);
			}
		}
		else if (ft_strcmp(data->tokens[i], "$") == 0)
			handle_dollar(data, &new, i);
		else
			new = realloc_append(new, data->tokens[i]);
		i++;
	}
	free_2d_array(&data->tokens);
	data->tokens = new;
	return (1);
}