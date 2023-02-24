#include "../headers/minishell.h"

t_list *ft_lstnew(char *var)
{
	t_list *list = (t_list *) malloc (sizeof(t_list));
	list ->str = var;
	list ->printed = 0;
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

t_list	*ft_lstcpy(t_list *lst)
{
	t_list	*head;
	t_list	*newlst;
	t_list	*newnode;

	newlst = NULL;
	head = lst;
	newlst = ft_lstnew(ft_strdup(lst->str));
	while (lst != NULL)
	{
		newnode = ft_lstnew(ft_strdup(lst->str));
		ft_lstadd_back(&newlst, newnode);
		lst = lst->next;
	}
	lst = head;
	return (newlst);
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

void	ft_lstfree(t_list *lst)
{
	t_list	*curr;
	t_list	*next;

	curr = lst;
	while (curr != NULL)
	{
		next = curr->next;
		free(curr->str);
		free(curr);
		curr = next;
	}
	lst = NULL;
}

void	ft_lstdel(t_list *lst)
{
	
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