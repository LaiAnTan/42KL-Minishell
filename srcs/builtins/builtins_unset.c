#include "../../headers/minishell.h"

int builtin_unset(char **args, t_data *data)
{
	int		i;
	char	*var_name;
	t_list	*node;
	t_list	*lst;

	i = 1;
	lst = data->vars;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "_") == 0)
			i++;
		node = find_var(lst, args[i]);
		if (node != NULL)
			ft_lstdel_env(&lst, node);
		i++;
	}
	return (0);
}