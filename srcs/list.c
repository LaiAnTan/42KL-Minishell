#include "../headers/minishell.h"

t_list *ft_lstnew(char *var)
{
	t_list *list = (t_list *) malloc (sizeof(t_list));
	list ->str = var;
	list ->next = NULL;
	return (list);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current -> next != NULL)
		current = current -> next;
	return (current);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if(!new)
		return ;
	if(lst == NULL)
		*lst = new;
	else
	{
		ft_lstlast(*lst) -> next = new;
		new -> next = NULL;
	}
}

void	ft_lstprint(t_list *lst)
{
	t_list *node;
	
	node = lst;
	while (node != NULL)
	{
		printf("%s\n", node->str);
		node = node->next;
	}
}