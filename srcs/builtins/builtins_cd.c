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
	else if (args[1][0] == '-')
	{
		builtin_pwd(data);
		return (0);
	}
	else
		cd_path = ft_strdup(args[1]);

	if (chdir(cd_path) == 0)
	{
		free(data->cwd);
		data->cwd = getcwd(NULL, PATH_MAX);
	}
	else
	{
		printf("cd: failed to change directory\n");
		return (1);
	}
	return (0);
}
