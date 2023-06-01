#include "../headers/minishell.h"

/*
this function checks if the character is part of the token group

token group is ' " | < > $
if it does, return a non-zero value
*/
int	is_token(char c)
{
	int		i = 0;
	char	token[9] = "\'\"|><$";
	
	while (token[i] != '\0')
	{
		if (token[i] == c)
			return (i + 1);
		i++;
	}
	return (0);
}

/*
this function handles the special index searching for bunny ears

specifically, the stop index

the start index would be at the first bunny ear found, the last index would be at the
last bunny ear found
*/
int	bunny_ears(char *line, int stop, int to_match)
{
	++stop;
	while (line[stop] && line[stop] != to_match)
		++stop;
	return (stop);
}

int	get_keyword(char *line, int stop)
{
	++stop;
	while (line[stop] && line[stop] != ' ' && !is_token(line[stop]))
		++stop;
	return (--stop);
}

/*
i find it hella stupid we cannot put comments in functions
*/
int	find_token_pos(char *line, int *index_pair)
{
	int		i;
	int		tk_type;

	if (index_pair[1] + 1 >= ft_strlen(line))
		return (-1);
	i = index_pair[1] + 1;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	index_pair[0] = i;
	tk_type = is_token(line[i]);
	if (tk_type != 0)
	{
		if (line[i + 1] != '\0' && (tk_type == 4 || tk_type == 5))
		{
			if (tk_type == is_token(line[i + 1]))
				i++;
		}
		else if (line[i + 1] != '\0' && tk_type == 6)
			i = get_keyword(line, i);
		if (tk_type == 1 || tk_type == 2)
			i = bunny_ears(line, i, line[i]);
	}
	else
	{
		while (line[i + 1] != '\0' && !is_token(line[i + 1]) && line[i] != ' ')
			i++;
	}
	index_pair[1] = i;
	return (tk_type);
}

int	lexer(t_data *data)
{
	int		len;
	int		token_pos[2];
	int		ret_val;
	char	*new_token;

	len = ft_strlen(data->line);
	data->tokens = (char **) malloc (sizeof(char *));
	if (!data->tokens)
		return (0);
	token_pos[1] = -1;
	data->tokens[0] = NULL;
	while (1)
	{
		ret_val = find_token_pos(data->line, token_pos);
		// use -1 if ended
		if (ret_val == -1 || token_pos[1] >= len)
			break ;
		new_token = ft_substr(data->line, token_pos[0], token_pos[1]);
		data->tokens = realloc_append(data->tokens, new_token);
		if (ret_val > 0 && ret_val != 1 && ret_val != 2)
			data->tokens = realloc_append(data->tokens, ft_strdup(""));
		free(new_token);
	}
	return (1);
}