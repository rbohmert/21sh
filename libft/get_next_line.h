/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbohmert <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/25 21:55:48 by rbohmert          #+#    #+#             */
/*   Updated: 2016/05/19 18:11:04 by rbohmert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 9999
# define MAX_FD 10
# include "libft.h"
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

char	*ft_realloc(char *buf, int size);
int		get_line(int fd, char **line, char *rest, int i);
int		sort(int fd, char **line, char *rest);
int		get_next_line(int fd, char **line);

#endif
