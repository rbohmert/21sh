#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	char	*new;
	int		i;
	
	i = -1;
	if (!(new = (char *)malloc(n + 1)))
		return (NULL);
	while (++i < n)
		new[i] = str[i];
	new[i] = 0;
	return (new);
}
