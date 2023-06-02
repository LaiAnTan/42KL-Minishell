#include "../headers/minishell.h"

/*
function used in variable substitution = $HOME
if the keyword given in name begins with a ?, it will immediately return the value of
the exit value of the last command

else, it will search for the variable in the env variable list, and then return the value
of the variable using get_val()

if the keyword cannot be found in the list, it returns ""

why the fuck are we writting documentation, no one is gonna read this other than us
*/
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

/*
function that searches a symbol stated in to_find in a string line

this function is very self-explanatory

returns the index if the symbol is found, else return -1
*/
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
	return (-1);
}

/*
this function.. is needed because norminette is a bitch

resets the temporary storage used in recombine_parts, freeing all the strings inside it
*/
void	reset_storage(char **temp_strings)
{
	int	i;

	i = -1;
	while (temp_strings[++i])
		free(temp_strings[i]);
}

/*
this function... is also needed because norminette is also a bitch

breaks down the line based on the indexes given
the value is stored inside the temporary storage in temp_strings

example = ls $SHLVL la
temp_string[0] = 'ls '
temp_string[1] = 'SHLVL'
temp_string[2] = ' la'
*/
void	break_down(char *line, int *indexes, char **temp_strings)
{
	temp_strings[0] = ft_substr(line, indexes[0], indexes[1] - 1);
	temp_strings[1] = ft_substr(line, indexes[1] + 1, indexes[2]);
	temp_strings[2] = ft_substr(line, indexes[2] + 1, ft_strlen(line));
}

/*
ah yes, another function needed because norminette, is a bitch

this function recombines all the strings found in temp_strings into a
single string using ft_append()

the recombined strings is stored in store
*/
void	recombine_parts(char **store, char **temp_strings, int *indexes)
{
	char	*ret;

	if ((*store))
		free((*store));
	ret = NULL;
	if (indexes[1] != indexes[0])
		ret = ft_append(ret, temp_strings[0]);
	ret = ft_append(ret, temp_strings[3]);
	ret = ft_append(ret, temp_strings[2]);
	(*store) = ret;
}

// i think of a better way tmr morning
void	replace_dollar(t_data *data)
{
	int		special_case;
	char	*ret;
	char	*string_storage[5];
	int		indexes[3];

	special_case = 0;
	ret = ft_strdup(data->line);
	indexes[0] = 0;
	indexes[1] = 0;
	string_storage[4] = NULL;
	while (search_symbol(&ret[indexes[1]], '$') != -1)
	{
		if (ret[indexes[1]] == '\"')
			special_case = !special_case;
		else if (ret[indexes[1]] == '\'' && !special_case)
		{
			++indexes[1];
			while (ret[indexes[1]] && ret[indexes[1]] != '\'')
				++indexes[1];
		}
		else if (ret[indexes[1]] == '$')
		{
			indexes[2] = get_keyword(ret, indexes[1]);
			break_down(ret, indexes, string_storage);
			string_storage[3] = access_var(data, string_storage[1]);
			recombine_parts(&ret, string_storage, indexes);
			reset_storage(string_storage);
			indexes[1] = 0;
		}
		++indexes[1];
	}
	printf("done replace --> %s\n", ret);
	free(data->line);
	data->line = ret;
}