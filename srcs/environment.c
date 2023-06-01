#include "../headers/minishell.h"

/*
function that converts the envp array of strings into a linked list
*/
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

/*
function that gets the position of the equal in an env variable
*/
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

/*
function that gets the value of the node passed as parameter
*/
char	*get_val(t_list *node)
{
	int		i;
	int		pos;
	char	*val;

	pos = get_equal_pos(node) + 1; // 1st char after =
	val = (char *) malloc (sizeof(char) * (ft_strlen(node->env.str) - pos + 1));
	i = 0;
	while (node->env.str[pos] != '\0')
	{
		val[i] = node->env.str[pos];
		i++;
		pos++;
	}
	val[i] = '\0';
	return (val);
}

/*
function that checks if the variable names are the same
*/
int	compare_name(char *var, char *name)
{
	int	i;

	i = 0;
	while (name[i] != '\0')
	{
		if (name[i] != var[i])
			return (0);
		++i;
	}
	if (var[i] == '=')
		return (1);
	return (0);
}

/*
function that finds and returns the node in which the variable to_find is located at
*/
t_list	*find_var(t_list *vars, char *to_find)
{
	t_list *node;

	node = vars;
	while (node != NULL)
	{
		if (compare_name(node->env.str, to_find) == 1)
			return (node);
		node = node->next;
	}
	return (NULL);
}

/*
function that converts the linked list of env variables into a 2d array inside data
*/
void	rebuild_envp(t_data *data)
{
	int		i;
	int		lst_size;
	t_list	*lst;
	t_list	*head;

	i = 0;
	lst = data->vars;
	lst_size = ft_lstsize(lst);
	head = lst;
	if (data->my_envp != NULL)
		free_2d_array(&data->my_envp);
	data->my_envp = (char **) malloc(sizeof(char *) * (lst_size + 1));
	while (lst != NULL)
	{
		data->my_envp[i] = ft_strdup(lst->env.str);
		i++;
		lst = lst->next;
	}
	data->my_envp[i] = NULL;
	lst = head;
}