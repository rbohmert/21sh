#include "libft.h"

t_2list		*ft_create_2lst(void *content)
{
	t_2list *elem;
	
	if (!(elem = (t_2list *)malloc(sizeof(t_2list))))
		return (NULL);
	else
	{
		elem->content = content;
		elem->next = NULL;
		elem->prev = NULL;
	}
	return (elem);
}
