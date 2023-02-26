#include "../headers/minishell.h"

int	find_next_cmd(char **tokens, int *index_pair)
{
	int		i;
	index_pair[0] = index_pair[1];
	i = index_pair[1] + 1;
	index_pair[0] = i;
	while (tokens[i] != NULL)
	{
		if (ft_strcmp(tokens[i + 1], "|") == 0)
		{
			index_pair[1] = i;
			return (1);
		}
		i++;
	}
	index_pair[1] = i;
	return (0);
}

char	**extract_cmd(char **tokens, int *index_pair)
{
	int		i;
	char	**cmd;

	
	find_next_cmd(tokens, index_pair);
	printf("%d | %d\n", index_pair[0], index_pair[1]);
	i = index_pair[0];
	cmd = (char **) malloc (sizeof(char *) * (index_pair[1] - index_pair[0] + 1));
	while (i < index_pair[1])
	{
		cmd[i] = ft_strdup(tokens[i]);
		i++;
	}
	cmd[i] = NULL;
	return (cmd);
}

int	parser(t_data *data)
{
	int		index_pair[2];
	char	**cmd;
	t_list	*lst;
	t_list	*node;

	index_pair[1] = -1;
	cmd = extract_cmd(data->tokens, index_pair);
	lst = ft_lstnew_cmd(cmd);
	while (1)
	{
		if (!find_next_cmd(data->tokens, index_pair))
			break ;
		cmd = extract_cmd(data->tokens, index_pair);
		node = ft_lstnew_cmd(cmd);
		ft_lstadd_back(&lst, node);
	}
	data->cmds = lst;
	return (1);
}