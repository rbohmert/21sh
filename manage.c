/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:20:02 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/25 04:16:05 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21.h"

int		manage_out(int outcom, t_list *out)
{
	t_list *tmp;
	char buf[2];
	int ret;
	int pid;

	if ((pid = fork()) < 0)
		ft_putstr("forkerror");
	else if (pid == 0)
	{
		while ((ret = read(outcom, buf, 1)))
		{
			tmp = out;
			while (tmp)
			{
				ft_putchar_fd(buf[0], (*((int*)(tmp->content))));
				tmp = tmp->next;
			}
		}
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

	pipe(pip);
	if ((pid = fork()) < 0)
		ft_putstr("forkerror");
	else if (pid == 0)
	{
		while (in)
		{
			while (read((*((int*)(in->content))), buf, 1))
			{
			//	printf("olol je lis dans %d et fdin = %d\n", (*((int*)(in->content))), fdin);
				//ft_putchar_fd(buf[0], 1);
				ft_putstr_fd(buf, pip[1]);
			}
			in = in->next;
		}
		exit(0);
	}
	close(pip[1]);
	return (pip[0]);
}

