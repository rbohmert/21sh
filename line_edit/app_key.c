#include "../includes/21.h"

//redirige selon la touche, annule le surlignage et les truc de copipaste si
//c'est pas un shift+fleche
void	app_key(char buf[10], t_sh *sh)
{
	if (ISCCARR(buf))
		shift_arrow(buf, sh);
	else if (ISCTRLY(buf))
		copy(sh);
	else if (sh->curscc != -1)
	{
		sh->curscc = -1;
		rewrite_line(sh);
	}
	if (ISARR(buf))
		arrow(buf, sh);
	if (ISIMPRC(buf))
		write_char(buf, sh);
	if (buf[0] == 127)
		del(sh);
	if (ISIMPRC(buf))
		ctrl(buf, sh);
	if (ISUDARR(buf))
		go_up_down(buf, sh);
	if (ISNPARR(buf))
		go_np_word(buf, sh);		
	curs_pos(sh);
}
//ici buf[0] = 1 -> ctrl-a ; buf[0]=2 ->ctrl-b...
void	ctrl(char buf[10], t_sh *sh)
{
	if (buf[0] == 1)
		sh->curs = 0;
	else if (buf[0] == 4)
		suppr(sh);
	else if (buf[0] == 16)
		paste(sh);
}
//les fleche + debut et fin + suppr
void	arrow(char buf[10], t_sh *sh)
{
	if (RARROW(buf))
		sh->curs == (sh->lenline) ? 0 : sh->curs++;
	if (LARROW(buf))
		!sh->curs ? 0 : sh->curs--;
	if (UARROW(buf))
		history_up(sh);
	if (DARROW(buf))
		history_down(sh);
	if (ENDARR(buf))
		sh->curs = sh->lenline;
	if (HOMARR(buf))
		sh->curs = 0;
	if (SUPPR(buf))
		suppr(sh);
}


