#include "../includes/line_edit.h"

//surligne suvant fleche gauche ou droite et bouge le curs en fonction et set 
//le curscc si il est pas mis
void	shift_arrow(char buf[6], t_sh *sh)
{
	if ((LSHFARR(buf) && sh->curs == 0) || (RSHFARR(buf) && sh->curs == sh->lenline))
		return ;
	if (sh->curscc == -1)
		sh->curscc = sh->curs;
	if (sh->curs >= sh->curscc && RSHFARR(buf))
	{
		PUT("mr");
		ft_putchar(sh->line[sh->curs]);
		PUT("me");
	}
	if (sh->curs <= sh->curscc && LSHFARR(buf))
	{
		PUT("mr");
		ft_putchar(sh->line[sh->curs]);
		PUT("me");
	}
	if (sh->curs < sh->curscc && RSHFARR(buf))
		ft_putchar(sh->line[sh->curs]);
	if (sh->curs > sh->curscc && LSHFARR(buf))
		ft_putchar(sh->line[sh->curs]);		
	if (LSHFARR(buf))
		sh->curs--;
	if (RSHFARR(buf))
		sh->curs++;
}

//copie la partie surligné, donc entre curs et curscc
void	copy(t_sh *sh)
{
	if (sh->curscc == -1)
		return ;
	if (sh->curs > sh->curscc)
		sh->copy = ft_strndup(sh->line + sh->curscc, sh->curs - sh->curscc);
	else if (sh->curs < sh->curscc)
		sh->copy = ft_strndup(sh->line + sh->curs + 1, sh->curscc - sh->curs);
	sh->curscc = -1;
	rewrite_line(sh);
}

//colle a l'endroit de curs la ligne contenue dans copie
void	paste(t_sh *sh)
{
	char *new;
	int l;
	int i;

	i = 0;
	l = sh->lenline;
	sh->lenline = ft_strlen(sh->line) + ft_strlen(sh->copy);
	new = ft_strnew(sh->lenline + 1);
	ft_strncat(new, sh->line, sh->curs);
	ft_strcat(new, sh->copy);
	ft_strcat(new, sh->line + sh->curs);
	free(sh->line);
	sh->line = new;
	rewrite_line(sh);
	if  ((l = sh->yfirstl + ((l + 2) / sh->win.ws_col)) == sh->win.ws_row) // si on etais a la derniere ligne du terminal
	{
		l = (sh->yfirstl + ((sh->lenline + 2) / sh->win.ws_col)) - l;
		while (i++ < l)	//remonter la 1er ligne d'autant de ligne que le nombre de nouvelle ligne ecrites
			sh->yfirstl--;
	}
	curs_pos(sh);
}
//reecrit toute la ligne, normalement. se met au debut et ecrit puis replace 
//le curseur
void	rewrite_line(t_sh *sh)
{
	tputs(tgoto(tgetstr("cm", NULL), 2, sh->yfirstl - 1), 1, ptchr);
	ft_putstr(sh->line);
	curs_pos(sh);
}


