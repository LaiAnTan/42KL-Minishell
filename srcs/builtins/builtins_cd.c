#include "../../headers/minishell.h"

int	builtin_cd(char **args, t_data *data)
{
	t_list		*node;

	int			size;
	char		*cd_path;

	size = count_2d_array(args);
	cd_path = NULL;
	if (size != 2)
		cd_path = ft_strdup("");
	else if (args[1][0] == '~')
	{
		node = find_var(data->vars, "HOME");
		if (node != NULL)
			cd_path = ft_strdup(get_val(node));
	}
	else if (args[1][0] == '-') // wrong
	{
		cd_path = access_var(data, "OLDPWD");
		if (ft_strlen(cd_path) == 0)
		{
			printf("cd: OLDPWD not set");
			return (1);
		}
		printf("%s\n", cd_path);
	}
	else
		cd_path = ft_strdup(args[1]);

	if (chdir(cd_path) == 0)
	{
		node = find_var(data->vars, "OLDPWD");
		if (node == NULL)
		{
			node = ft_lstnew_env(ft_strdup(ft_append(ft_strdup("OLDPWD="), data->cwd)));
			ft_lstadd_back(&data->vars, node);
		}
		else
			node->env.str = ft_strdup(ft_append(ft_strdup("OLDPWD="), data->cwd));
		free(data->cwd);
		data->cwd = getcwd(NULL, PATH_MAX);
		node = find_var(data->vars, "PWD");
		if (node == NULL)
		{
			node = ft_lstnew_env(ft_strdup(ft_append(ft_strdup("PWD="), data->cwd)));
			ft_lstadd_back(&data->vars, node);
		}
		else
			node->env.str = ft_strdup(ft_append(ft_strdup("PWD="), data->cwd));
		data->last_exit = 0;
	}
	else
	{
		printf("cd: %s: no such file or directory\n", cd_path);
		return (1);
	}
	return (0);
}
