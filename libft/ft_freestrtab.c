#include "libft.h"

void	ft_freestrtab(char **strtab)
{
	int i;

	if (strtab == NULL)
		return;
	i = 0;
	while(strtab[i])
		free(strtab[i++]);
	free(strtab);
}
