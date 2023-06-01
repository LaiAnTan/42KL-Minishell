#include "../headers/minishell.h"

char	*access_var(t_data *data, char *name) 
{
	t_list	*lst;

	lst = data->vars;
	if (!name)
		return (ft_strdup(""));
	if (name[0] == '?')
		return (ft_itoa(data->last_exit));
	while (lst)
	{
		if (ft_strcmp_equals(lst->env.str, name) == 0)
			return(get_val(lst));
		lst = lst->next;
	}
	return (ft_strdup(""));
}

int		search_symbol(char *line, int to_find)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == to_find)
			return (i);
		++i;
	}
	return -1;
}

void	reset_storage(char **temp_strings)
{
	int	i;

	i = -1;
	while (temp_strings[++i])
		free(temp_strings[i]);
}

void	break_down(char *line, int *indexes, char **temp_strings)
{
	// example = ls $SHLVL la
	// temp_string[0] = 'ls '
	// temp_string[1] = 'SHLVL'
	// temp_string[2] = ' la'

	temp_strings[0] = ft_substr(line, indexes[0], indexes[1] - 1);
	temp_strings[1] = ft_substr(line, indexes[1] + 1, indexes[2]);
	temp_strings[2] = ft_substr(line, indexes[2] + 1, ft_strlen(line));
}

char	*recombine_parts(char **temp_strings, int *indexes)
{
	char	*ret;

	ret = NULL;
	if (indexes[1] != indexes[0])
		ret = ft_append(ret, temp_strings[0]);
	ret = ft_append(ret, temp_strings[3]);
	ret = ft_append(ret, temp_strings[2]);
	return (ret);
}

char	*handle_dollar(t_data *data, char *line)
{
	char	*ret;
	// lord forgive me for i have sinned
	char	*temp_strings[5];
	int		indexes[3];

	ret = ft_strdup(line);
	indexes[0] = 0;
	temp_strings[4] = NULL;
	while (1)
	{
		// get the start of the keyword
		indexes[1] = search_symbol(ret, '$');

		// no more dollar signs = no more variables
		if (indexes[1] == -1)
			return (ret);

		// get the end of the keyword
		indexes[2] = get_keyword(ret, indexes[1]);

		// $?
		if (ret[indexes[1] + 1] == '?')
			indexes[2] = indexes[1] + 1;
		break_down(ret, indexes, temp_strings);

		temp_strings[3] = access_var(data, temp_strings[1]);

		free(ret);
		ret = NULL;
		ret = recombine_parts(temp_strings, indexes);

		reset_storage(temp_strings);
	}
}

char	**worry_about_spaces(char **ori, char *might_have_space)
{
	int	start;
	int	end;

	start = 0;
	while (1)
	{
		end = search_symbol(&might_have_space[start], ' ');
		if (end == -1)
		{
			end = ft_strlen(might_have_space);
			return (realloc_append(ori, ft_substr(might_have_space, start, end)));
		}
		end += start;
		if ((end - start) > 0)
		{
			ori = realloc_append(ori, ft_substr(might_have_space, start, end - 1));
			// so that the parser can do its job
			ori = realloc_append(ori, "");
		}
		printf("%d, %d\n", start, end);
		start = end + 1;
	}
}

int	expander(t_data *data)
{
	int		i;
	char	**new;
	int		tokencount = count_2d_array(data->tokens);

	i = 0;
	new = malloc (sizeof(char *));
	new[0] = NULL;
	if (!data || !data->tokens)
		return (0);
	while (i < tokencount)
	{
		if (data->tokens[i][0] == '\"')
		{
			new = realloc_append(new, handle_dollar(data, data->tokens[i]));
			i++;
		}
		else if (data->tokens[i][0] == '\'')
		{
			new = realloc_append(new, data->tokens[i]);
			i++;
		}
		else
		{
			new = worry_about_spaces(new, handle_dollar(data, data->tokens[i]));
			i++;
		}
	}
	free_2d_array(&data->tokens);
	data->tokens = new;
	return (1);
}
