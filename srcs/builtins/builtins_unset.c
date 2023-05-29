#include "../../headers/minishell.h"

void builtin_unset(char **args, t_data *data)
{
	int		i;
	char	*var_name;
	t_list	*node;
	t_list	*lst;

	i = 1;
	lst = data->vars;
	while (args[i] != NULL)
	{
		node = find_var(lst, args[i]);
		if (node != NULL)
		{
			printf("variable found, %s\n", node->env.str);
			ft_lstdel_env(&lst, node);
		}
		i++;
	}
}