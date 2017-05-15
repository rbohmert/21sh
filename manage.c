/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 16:20:02 by rbohmert          #+#    #+#             */
/*   Updated: 2017/03/31 10:59:50 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/21.h"

//attend sur le fd donné (lecture du pipe) et reecrit dans tout les fd de out
int		manage_out(int outcom, t_list *out, t_list *toclose, int assoc_pid)
{
	t_list *tmp;
	char buf[2];
	int pid;

	if ((pid = fork()) < 0)
		ft_putstr("forkerror");
	else if (pid == 0)
	{
		signal(SIGPIPE, SIG_IGN);
		multiclose(toclose);
		while (read(outcom, buf, 1))
		{
			tmp = out;
			while (tmp)
			{
				if (write(tmp->content_size, buf, 1) == -1)
				{
					
					kill(assoc_pid, SIGINT);
					exit(0);
				}
				tmp = tmp->next;
			}
		}
		exit(0);
	}
	close(outcom);
	return (0);
}

//attend tour a tour sur tout les fd de in et reecrit dans le pipe
int		manage_in(t_list *in, t_list *toclose)
{
	pid_t pid;
	char buf[2];
	int  pip[2];

	pipe(pip);
	if ((pid = fork()) < 0)
		ft_putstr("forkerror");
	else if (pid == 0)
	{	
		signal(SIGPIPE, SIG_IGN);
		multiclose(toclose);
		close(pip[0]);
		while (in)
		{
			while (read(in->content_size, buf, 1))
			{
				if (write(pip[1], buf, 1) == -1)
					exit(0);
			}
			in = in->next;
		}
		exit(0);
	}
	close(pip[1]);
	return (pip[0]);
}

