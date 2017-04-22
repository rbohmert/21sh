#include "libft.h"

void	ft_push_2back(t_2list **lst, void *content)
{
	t_2list *tmp;

	tmp = *lst;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = ft_create_2lst(content);
		tmp->next->prev = tmp;
	}
	else
		*lst = ft_create_2lst(content);
}
