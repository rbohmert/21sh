#include "../includes/21.h"

int			ptchr(int i)
{
	write(STDIN_FILENO, &i, 1);
	return (0);
}
//sav sh dans une static
t_sh	*get_sh(t_sh *sh)
{
	static t_sh *save;
	
	if (sh == NULL)
		return (save);
	save = sh;
	return (NULL);
}

//replace le curseur ou il faut en fonction du y de la premiere ligne
//et de la position du curseur dans la ligne
void	curs_pos(t_sh *sh)
{
	int x;
	int y;

	//ft_putnbr(((sh->lenline + 2) / sh->win.ws_col));	
	//ft_putnbr(sh->yfirstl);	
	x = (sh->curs + 2) % sh->win.ws_col;
	y = (sh->yfirstl - 1) + ((sh->curs + 2) / sh->win.ws_col);
	tputs(tgoto(tgetstr("cm", NULL), x, y), 1, ptchr);
}

//get la ligne ou est le curseur
int		get_curs_y()
{
	char b[15];
	char *tmp;
	int i;
	int j;
	int k;

	i = -1;
	j = 0;
	bzero(b, 15);
	while (b[0] != 27 && b[1] != 91)// && b[ft_strlen(b) - 1] != 'R')
	{
		bzero(b, 15);
		ft_putstr("\x1B[6n");
		read(0, b, 15);
	}
	while (!ft_isdigit(b[++i]))
		;
	k = i;
	while (b[i++] != ';')
		j++;
	tmp = ft_strndup(b + k, j);
	i = ft_atoi(tmp);
	free(tmp);
	return (i);
}
