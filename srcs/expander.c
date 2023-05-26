#include "../headers/minishell.h"

// yep, no idea how to handle this garbage

// instead of append it to the new array, i return the value
// mm yes should work mhm
char	*handle_dollar(t_data *data, char ***new, int *dollar_pos)
{
	char	*val;

	t_list	*node;

	if (data->tokens[*dollar_pos] == NULL)
		return (NULL);
	if (ft_strcmp(data->tokens[*dollar_pos], "$") == 0)
	{
		(*dollar_pos)++;
		if (data->tokens[*dollar_pos] != NULL)
		{
			node = find_var(data->vars, data->tokens[*dollar_pos]);
			if (node == NULL)
				return (NULL);
			// note to me, free node
			return (node->env.str);
		}
	}
	else
		// *new = realloc_append(*new, data->tokens[*dollar_pos]);
		return (ft_strdup(data->tokens[*dollar_pos]));
}

// i will now fix this in the most laziest way possible
// it will be garbage but im lazy to type so

void reset(char **stuff)
{
	free(*stuff);
	*stuff = NULL;
}

int	expander(t_data *data)
{
	int		i;
	char	**new;
	char	*temp;
	int		tokencount = count_2d_array(data->tokens);

	i = 0;
	temp = NULL;
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
				temp = ft_append(temp, data->tokens[i]);
				i++;
			}
			new = realloc_append(new, temp);
			reset(&temp);
			i++;
		}
		else if (ft_strcmp(data->tokens[i], "\"") == 0)
		{
			i++;
			while (data->tokens[i] != NULL && ft_strcmp(data->tokens[i], "\"") != 0)
			{
				temp = ft_append(temp, handle_dollar(data, &new, &i));
				i++;
			}
			new = realloc_append(new, temp);
			reset(&temp);
			i++;
		}
		else
		{
			new = realloc_append(new, handle_dollar(data, &new, &i));
			i++;
		}
	}
	free_2d_array(&data->tokens);
	data->tokens = new;
	return (1);
}


/*

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

*/
