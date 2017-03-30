/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:20:02 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/29 17:29:05 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21.h"

void put(t_list *l)
{
	ft_putendl("*************************");
	while (l)
	{
		//close(*((int *)(l->content)));
		ft_putnbr(*((int *)(l->content)));
		ft_putchar('\n');
		l=l->next;
	}
	ft_putendl("*************************");
}

int		manage_out(int outcom, t_list *out)
{
	t_list *tmp;
	char buf[2];
	int ret;
	int pid;

	ft_putstr("out");
	put(out);
	if ((pid = fork()) < 0)
		ft_putstr("forkerror");
	else if (pid == 0)
	{
		while ((ret = read(outcom, buf, 1)))
		{
			tmp = out;
			while (tmp)
			{
				write((*((int*)(tmp->content))), buf, 1);
				tmp = tmp->next;
			}
		}
		ft_putstr("fin de manage out");
		exit(0);
	}
	close(outcom);
	return (0);
}

int		manage_in(t_list *in)
{
	pid_t pid;
	char buf[2];
	int  pip[2];

	ft_putstr("in");
	put(in);
	pipe(pip);
	ft_putendl("&&&&&&&pipe du in&&&&&&&&&&");
	ft_putnbr(pip[0]);
	ft_putchar (' ');
	ft_putnbr(pip[1]);
	ft_putchar ('\n');
	ft_putendl("&&&&&&&&&&&&&&&&&");
	if ((pid = fork()) < 0)
		ft_putstr("forkerror");
	else if (pid == 0)
	{
		while (in)
		{
			while (read((*((int*)(in->content))), buf, 1))
				write(pip[1], buf, 1);
			in = in->next;
			ft_putstr("0");
		}
		ft_putstr("fin de manage in");
		exit(0);
	}
	close(pip[1]);
	return (pip[0]);
}

