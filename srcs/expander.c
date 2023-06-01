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
	return -1;
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

returns the recombined strings
*/
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

/*
function that handles the replacement of $ sign

checks for and replaces variables in a token (which is given in line)

returns the new string with its variable replaced
*/
char	*handle_dollar(t_data *data, char *line)
{
	char	*ret;
	char	*temp_strings[5];
	int		indexes[3];

	ret = ft_strdup(line);
	indexes[0] = 0;
	temp_strings[4] = NULL;
	while (1)
	{
		indexes[1] = search_symbol(ret, '$');
		if (indexes[1] == -1)
			return (ret);
		indexes[2] = get_keyword(ret, indexes[1]);
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

/*
this function is needed because bash is a bitch

this functions takes in the substituded line in (line) and checks if it has spaces
if it does, it will be seperated and treated as its single token

if a space is detected, the first half will be extracted and appended, then, a 
"" token will be appended due to how the parser works

required for $TEST="ho hi", ec$TEST to work
*/
char	**worry_about_spaces(char **ori, char *line)
{
	char	**ret;
	int		start;
	int		end;

	start = 0;
	while (1)
	{
		end = search_symbol(&line[start], ' ');
		if (end == -1)
		{
			end = ft_strlen(line);
			ret = realloc_append(ori, ft_substr(line, start, end));
			return (ret);
		}
		end += start;
		if ((end - start))
		{
			ori = realloc_append(ori, ft_substr(line, start, end - 1));
			if (line[end + 1] != '\0')
				ori = realloc_append(ori, "");
		}
		start = end + 1;
	}
}

/*
this function is le expander

it checks and replaces all the variables ($ signs) in the token
creates a new list with all the tokens with its variable replaced
frees original token list
*/
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
