#include "libft.h"

void	ft_push_2front(t_2list **lst, void *content)
{
	t_2list *tmp;

	tmp = *lst;
	if (tmp)
	{
		tmp = ft_create_2lst(content);
		tmp->next = *lst;
		(*lst)->prev = tmp;
		*lst = tmp;
	}
	else
		*lst = ft_create_2lst(content);
}
