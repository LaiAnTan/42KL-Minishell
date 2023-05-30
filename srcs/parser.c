#include "../headers/minishell.h"

int	find_next_cmd(char **tokens, int *index_pair)
{
	int	i;

	if (!tokens)
		return (0);
	if (ft_strcmp(tokens[index_pair[1]], "|") == 0)
		++index_pair[1];

	index_pair[0] = index_pair[1];
	i = index_pair[1];

	while (tokens[i] != NULL)
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			index_pair[1] = i;
			break;
		}
		i++;
	}
	index_pair[1] = i;
	return (0);
}

char	**extract_cmd(char **tokens, int *index_pair)
{
	int		j;
	int		filled;
	char	**cmd;
	char	*str;

	find_next_cmd(tokens, index_pair);
	j = index_pair[0];
	str = NULL;
	cmd = malloc (sizeof(char *));
	cmd[0] = NULL;
	filled = 0;
	while (j < index_pair[1])
	{
		if (ft_strlen(tokens[j]) == 0 && filled)
		{
			cmd = realloc_append(cmd, ft_strdup(str));
			free(str);
			str = NULL;
			filled = 0;
		}
		else
		{
			tokens[j] = ft_trimstr(tokens[j], ' ');
			str = ft_append(str, tokens[j]);
			filled = 1;
		}
		++j;
	}
	if (str)
	{
		cmd = realloc_append(cmd, ft_strdup(str));
		free(str);
	}
	return (cmd);
}

void	remove_ears(t_data *data)
{
	int	i; 

	i = 0; 
	while (data->tokens[i])
	{
		if (data->tokens[i][0] == '\"')
			data->tokens[i] = ft_trimstr(data->tokens[i], '\"');
		else if (data->tokens[i][0] == '\'')
			data->tokens[i] = ft_trimstr(data->tokens[i], '\'');
		++i;
	}
}

int	parser(t_data *data)
{
	int		index_pair[2];
	char	**cmd;
	t_list	*lst;
	t_list	*node;

	remove_ears(data);
	index_pair[1] = 0;
	cmd = extract_cmd(data->tokens, index_pair);
	lst = ft_lstnew_cmd(cmd);
	while (data->tokens[index_pair[1]])
	{
		cmd = extract_cmd(data->tokens, index_pair);
		node = ft_lstnew_cmd(cmd);
		ft_lstadd_back(&lst, node);
	}
	free_2d_array(&data->tokens);
	data->cmds = lst;
	return (1);
}