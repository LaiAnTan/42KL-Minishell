#include "../headers/minishell.h"

/*
symbols to be handled

single quotation		'
double quotation		"
pipes					|

redirect input			<
redirect output			>
delimiter				<<
append					>>

variable expansion		$
exec status of last cmd	$?
else keyword

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

// hmm would this work
// you know this could be flags, but like im lazy so

// also god i hate these terms, will change to better ones later
# define DO_NOT_IGNORE_SPACE	0
# define IGNORE_SPACE			1
# define STOP_ON_SPACE			2
# define IF_IGNORE_SPACE		(*have_spaces) == IGNORE_SPACE
# define IF_DO_NOT_IGNORE_SPACE	(*have_spaces) == DO_NOT_IGNORE_SPACE
# define IF_STOP_ON_SPACE		(*have_spaces) == STOP_ON_SPACE

int	find_token_pos(char *line, int *index_pair, int *have_spaces)
{
	int		i;
	int		tk_type;

	// check if the index is on '\0' symbol, if it is kill it with fire
	if (index_pair[1] + 1 >= ft_strlen(line))
		return (0);
	index_pair[0] = index_pair[1] + 1;
	i = index_pair[0];
	// fuck you bunny ears
	if (IF_DO_NOT_IGNORE_SPACE)
	{
		while (line[i] != '\0' && line[i] == ' ')
			i++;
		index_pair[0] = i;
	}
	tk_type = is_token(line[i]);
	// handles identifier
	if (tk_type != 0)
	{
		// handles  < and > 
		if (line[i + 1] != '\0' && (tk_type == 4 || tk_type == 5))
		{
			// handles << and >>
			if (tk_type == is_token(line[i + 1]))
				i++;
		}
		// handles $
		else if (line[i + 1] != '\0' && tk_type == 6)
		{
			if (line[i + 1] == '?')
				i++;
			else
				*have_spaces = STOP_ON_SPACE;
		}
		if (line[i] == '\'' || line[i] == '\"')
			// flip flop
			*have_spaces = !(*have_spaces == IGNORE_SPACE);
	}
	// handles everything else
	else
	{
		while (line[i] != '\0' && !is_token(line[i]))
		{
			// this is a pain in the ass
			if (line[i] == ' ' && (IF_DO_NOT_IGNORE_SPACE || IF_STOP_ON_SPACE))
			{	
				if (IF_STOP_ON_SPACE)
					*have_spaces = IGNORE_SPACE;
				break;
			}
			i++;
		}
		--i;
	}
	index_pair[1] = i;
	return (1);
}

// will now attempt to fix the "" this symbol
// expect horrendous code cause i lazy change

int	lexer(t_data *data)
{
	int		len;
	int		token_pos[2];
	char	*new_token;
	
	int		have_space;

	have_space = DO_NOT_IGNORE_SPACE;
	len = ft_strlen(data->line);
	data->tokens = (char **) malloc (sizeof(char *));
	if (!data->tokens)
		return (0);
	token_pos[1] = -1;
	data->tokens[0] = NULL;
	while (1)
	{
		if (!find_token_pos(data->line, token_pos, &have_space) || token_pos[1] >= len)
			break ;
		new_token = ft_substr(data->line, token_pos[0], token_pos[1]);
		data->tokens = realloc_append(data->tokens, new_token);
		free(new_token);
	}

	printf("in tokens:\n");
	for (int i = 0; data->tokens[i]; ++i)
		printf("%d -- %s\n", i, data->tokens[i]);
	return (1);
}