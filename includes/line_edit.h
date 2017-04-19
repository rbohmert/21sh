#ifndef LINE_EDIT_H
# define LINE_EDIT_H

# include <termios.h>
# include <sys/ioctl.h>
# include <termcap.h>
//# include <curses.h>
# include <term.h>
# include <stdio.h>
# include <signal.h>
# include "../libft/libft.h"
# include "21.h"
# include "minishell.h"
# define ISARR(x) (x[0] == 27 && x[1] == 91 && x[4] == 0)
# define ISIMPRC(x) (x[0] > 31 && x[0] < 127 && x[1] == 0)
# define RARROW(x) (x[2] == 67 && x[3] == 0)
# define LARROW(x) (x[2] == 68 && x[3] == 0)
# define UARROW(x) (x[2] == 65 && x[3] == 0)
# define DARROW(x) (x[2] == 66 && x[3] == 0)
# define HOMARR(x) (x[2] == 54 && x[3] == 126)
# define ENDARR(x) (x[2] == 53 && x[3] == 126)
# define SUPPR(x) (x[2] == 51 && x[3] == 126)
# define PUT(x) tputs(tgetstr(x, NULL), 1, ptchr)
# define ISCTRL(x) ((x[0] >= 1 && x[0] <= 26) && x[1] == 0)
//# define ISCCARR(x) ((!ft_strncmp(x, "\x1B[1;2", 5)) && (x[5] == 67 || x[5] == 68))
# define ISCCARR(x) ((!ft_strncmp(x, "\x1B[1;2", 5)) && (x[5] == 67 || x[5] == 68)) // SHIFT +LR copier coller arrow
# define ISUDARR(x) ((!ft_strncmp(x, "\x1B[1;5", 5)) && (x[5] == 65 || x[5] == 66)) // CTRL + UD up down arrow
# define ISNPARR(x) ((!ft_strncmp(x, "\x1B[1;2", 5)) && (x[5] == 65 || x[5] == 66)) // SHIFT + UD next previous arrow
//# define ISUDARR(x) (!ft_strncmp(x, "\x1B[1;2", 5) && (x[5] == 65 || x[5] == 66))
# define USHFARR(x) (x[5] == 65)
# define DSHFARR(x) (x[5] == 66)
# define RSHFARR(x) (x[5] == 67)
# define LSHFARR(x) (x[5] == 68)
# define ISCTRLY(x) (x[0] == 25 && x[1] == 0)
# define ISBLANC(x) (x == '\t' || x== '\v' || x == ' ')

typedef struct s_sh
{
	struct termios term;//option du terminal a renvoyer pour mode canonique ect..
	struct termios tsav;//sav du term pour restaurer
	struct winsize win;//taille fenetre
	char	*line;//line en cour
	char	*copy;//bout copier
	int		curs;//position du curseur dans la ligne de commande
	int		curscc;//pos curseur debut de surlignage
	int		lenline;//taille de la line
	int		yfirstl;//y de la premiere ligne de la ligne de commande
}				t_sh;

int		ptchr(int i);
t_sh	*get_sh(t_sh *sh);
int		get_curs_y(void);
int		restore_term(t_sh *sh);
int		init_term(t_sh *sh);
void	curs_pos(t_sh *sh);
void	suppr(t_sh *sh);
void	del(t_sh *sh);
void	arrow(char buf[6], t_sh *sh);
void	write_char(char buf[6], t_sh *sh);
void	rewrite_line(t_sh *sh);
void	shift_arrow(char buf[6], t_sh *sh);
void	copy(t_sh *sh);
void	paste(t_sh *sh);
void	ctrl(char buf[6], t_sh *sh);
void	go_up_down(char buf[6], t_sh *sh);
void	go_np_word(char buf[6], t_sh *sh);
void	app_key(char buf[6], t_sh *sh);
char	*get_line_tcap(void);
void	sighandler(int sig);
void	block_sig(void);

#endif
