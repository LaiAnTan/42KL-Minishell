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