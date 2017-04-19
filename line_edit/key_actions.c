#include "../includes/line_edit.h"
//touche suppr, supprime le char de la line dans le memoire et reecrit 
void	suppr(t_sh *sh)
{
	char *new;

	if (!sh->lenline || sh->lenline == sh->curs)
		return ;
	new = ft_strnew(sh->lenline + 1);
	ft_strncat(new, sh->line, sh->curs);
	ft_strcat(new, sh->line + sh->curs + 1);
	free(sh->line);
	sh->line = new;
	sh->lenline--;
	ft_putstr(sh->line + sh->curs);
	ft_putchar(' ');
	ft_putchar(' ');
}
//touche backspace, presque pareil que suppr donc 
void	del(t_sh *sh)
{
	char *new;

	if (!sh->curs)
		return ;
	new = ft_strnew(sh->lenline + 1);
	ft_strncat(new, sh->line, sh->curs - 1);
	ft_strcat(new, sh->line + sh->curs);
	free(sh->line);
	sh->line = new;
	sh->lenline--;
	sh->curs--;
	PUT("le");
	ft_putstr(sh->line + sh->curs);
	ft_putchar(' ');
	ft_putchar(' ');
}	

//insere un char dans line en memoire, reecrit le bout de ligne et 
//avance le curseur 
void	write_char(char buf[6], t_sh *sh)
{
	char *new;

	if (!(new = ft_strnew(sh->lenline + 2)))
		return ;
	ft_strncat(new, sh->line, sh->curs);
	ft_strcat(new, buf);
	ft_strcat(new, sh->line + sh->curs);
	free(sh->line);
	sh->line = new;
	ft_putstr(sh->line + sh->curs);
	ft_putchar(' ');
	sh->curs++;
	sh->lenline++;
	if (!((sh->lenline + 2) % sh->win.ws_col) && (sh->yfirstl-1 + ((sh->lenline + 2) / sh->win.ws_col)) == sh->win.ws_row)
		sh->yfirstl--;

}
//place le curseur une ligne au dessus ou en dessous, si possible
void go_up_down(char buf[6], t_sh *sh)
{
	if ((USHFARR(buf) && sh->curs - sh->win.ws_col < 0) || (DSHFARR(buf) && sh->curs + sh->win.ws_col > sh->lenline))
		return ;
	if (USHFARR(buf))
		sh->curs = sh->curs - sh->win.ws_col;
	if (DSHFARR(buf))
		sh->curs = sh->curs + sh->win.ws_col;
}
//va au mot precedent ou suivant si possible
void go_np_word(char buf[6], t_sh *sh)
{
	int i = sh->curs;
	
	while (!ISBLANC(sh->line[i]) && i < sh->lenline)
		i++;
	while (ISBLANC(sh->line[i]) && i < sh->lenline)
		i++;
	if (i >= sh->lenline && USHFARR(buf))
		return ;
	if (USHFARR(buf))
	{
		while (!ISBLANC(sh->line[sh->curs]))
			sh->curs++;
		while (ISBLANC(sh->line[sh->curs]))
			sh->curs++;
	}
	if (DSHFARR(buf))
	{
		if	(sh->curs > 0 && ISBLANC(sh->line[sh->curs - 1]))
				sh->curs--;
		if (ISBLANC(sh->line[sh->curs]))
		{
			while (ISBLANC(sh->line[sh->curs]))
				sh->curs--;
			while (!ISBLANC(sh->line[sh->curs]) && sh->curs >= 0)
				sh->curs--;
			sh->curs++;
		}
		else 
		{
			while (!ISBLANC(sh->line[sh->curs]) && sh->curs >= 0)
				sh->curs--;
			sh->curs++;
		}
	}	
}
