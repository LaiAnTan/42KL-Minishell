#include "../../headers/minishell.h"

void	ft_lstfree(t_list **lst)
{
	t_list	*curr;
	t_list	*next;

	curr = *lst;
	while (curr != NULL)
	{
		next = curr->next;
		if (curr->env.str != NULL)
			free(curr->env.str);
		if(curr->cmd.cmd != NULL)
			free_2d_array(&curr->cmd.cmd);
		free(curr);
		curr = next;
	}
	*lst = NULL;
}

void	ft_lstdel_env(t_list **lst, t_list *node)
{
	t_list	*head;
	t_list	*prev;

	head = *lst;
	if (head == node)
	{
		head = head->next;
		return ;
	}
	prev = head;
	while (prev->next != node)
		prev = prev->next;
	prev->next = node->next;
	free(node);
	return ;
}

int		ft_lstsize(t_list *lst)
{
	size_t i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}