#include "../../headers/minishell.h"

/*
thou shall regret asking me to do documentation

function for the cd command in bash
handles the changing in directory and 
  - symbol => is broken, cd - is broken 
  ~ symbol => goes back to the directory stated in $HOME
*/
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
		data->last_exit = 0;
	}
	else
	{
		printf("cd: %s: no such file or directory\n", cd_path);
		return (1);
	}
	return (0);
}
