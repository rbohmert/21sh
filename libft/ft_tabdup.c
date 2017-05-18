#include "libft.h"

char **ft_tabdup(char **tab)
{
	int		i;
	char	**ntab;

	i = -1;
	while (tab[++i])
		;
	if (!(ntab = malloc((i + 1) * sizeof(char *))))
		return (NULL);
	i = -1;
	while (tab[++i])
		ntab[i] = ft_strdup(tab[i]);
	ntab[i] = NULL;
	return (ntab);
}
