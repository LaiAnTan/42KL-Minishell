#include "../headers/minishell.h"

t_list	*set_env(char **envp)
{
	int		i;
	t_list	*vars;
	t_list	*node;


	i = 1;	
	vars = ft_lstnew_env(envp[0]);
	while (envp[i] != NULL)
	{
		node = ft_lstnew_env(envp[i]);
		ft_lstadd_back(&vars, node);
		i++;
	}
	return (vars);
}

int	get_equal_pos(t_list *node)
{
	int		pos;

	pos = 0;
	while (node->env.str[pos] != '\0')
	{
		if (node->env.str[pos] == '=')
			return (pos);
		pos++;
	}
	return (-1);
}

char	*get_val(t_list *node)
{
	int		i;
	int		pos;
	char	*val;

	pos = get_equal_pos(node) + 1; // 1st char after =
	val = (char *) malloc (sizeof(char) * (ft_strlen(node->env.str) - pos + 1));
	while (node->env.str[pos] != '\0')
	{
		val[i] = node->env.str[pos];
		i++;
		pos++;
	}
	val[i] = '\0';
	return (val);
}