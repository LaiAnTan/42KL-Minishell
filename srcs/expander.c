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

// yep, no idea how to handle this garbage

// instead of append it to the new array, i return the value
// mm yes should work mhm
char	*handle_dollar(t_data *data, char ***new, int *dollar_pos)
{
	char	*val;

	if (data->tokens[*dollar_pos] == NULL)
		return (NULL);
	if (ft_strcmp(data->tokens[*dollar_pos], "$") == 0)
	{
		(*dollar_pos)++;
		if (data->tokens[*dollar_pos] != NULL)
		{
			val = find_var(data, data->tokens[*dollar_pos]);
			(*dollar_pos)++;
			if (val == NULL)
				return (NULL);
			// note to me, free val
			return (val);
		}
	}
	else
		// *new = realloc_append(*new, data->tokens[*dollar_pos]);
		return (ft_strdup(data->tokens[*dollar_pos]));
}

/* append()
**
** USAGE
** accepts two string as parameter
** str1 and str2
** frees str1
** this function would (hopefully), append str2 to str1


** RETURN VALUE
** the newly appended string, which is MALLOCED
*/
char	*append(char *str1, char *str2)
{
	char	*ret;
	int		i;
	int		j;

	if (!str1 && !str2)
		return NULL;
	ret = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	i = 0;
	while (str1 && str1[i])
	{
		ret[i] = str1[i];
		++i;
	}
	j = 0;
	while (str2 && str2[j])
	{
		ret[i] = str2[j];
		++i;
		++j;
	}
	ret[i] = '\0';

	if (str1)
		free(str1);

	return (ret);
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
	int		tokencount = count_double(data->tokens);

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
				// mfw no append function
				temp = append(temp, data->tokens[i]);
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
				temp = append(temp, handle_dollar(data, &new, &i));
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
