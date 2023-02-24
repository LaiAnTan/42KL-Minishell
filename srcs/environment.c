#include "../headers/minishell.h"

t_list	*set_env(char **envp)
{
	int		i;
	t_list	*vars;
	t_list	*node;


	i = 1;	
	vars = ft_lstnew(envp[0]);
	while (envp[i] != NULL)
	{
		node = ft_lstnew(envp[i]);
		ft_lstadd_back(&vars, node);
		i++;
	}
	return (vars);
}

int	get_equal_pos(t_list *node)
{
	int		pos;

	pos = 0;
	while (node->str[pos] != '\0')
	{
		if (node->str[pos] == '=')
			return (pos);
		pos++;
	}
	return (-1);
	
}