/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:35:31 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/22 11:02:07 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

#include <stdio.h>

static int			ft_search_fd(int fd, t_file_read **fd_save,
														t_file_read **fd_called)
{
	t_file_read *suiv;

	*fd_called = *fd_save;
	while ((*fd_called) && (*fd_called)->next)
	{
		if ((*fd_called)->fd == fd)
			return (1);
		*fd_called = (*fd_called)->next;
	}
	if (*fd_called && (*fd_called)->fd == fd)
		return (0);
	if (!(suiv = (t_file_read*)malloc(sizeof(t_file_read))))
		return (-1);
	suiv->fd = fd;
	if (!(suiv->remain = ft_strnew(0)))
		return (-1);
	suiv->next = NULL;
	if (*fd_save)
		(*fd_called)->next = suiv;
	else
		*fd_save = suiv;
	*fd_called = suiv;
	return (0);
}

static void			fill_fd(int fd, int *ret_read, t_file_read *fd_called)
{
	char	*buffer;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	buffer = NULL;
	tmp = NULL;
	if (!(buffer))
		if (!(buffer = ft_strnew(BUFF_SIZE_GNL)))
			return ;
	*ret_read = read(fd, buffer, BUFF_SIZE_GNL);
	(*ret_read == -1 || *ret_read == 0 ? ft_strdel(&buffer) : 0);
	if (*ret_read == -1 || *ret_read == 0)
		return ;
	tmp = fd_called->remain;
	fd_called->remain = ft_strjoin(tmp, buffer);
	ft_strdel(&tmp);
	while (fd_called->remain[i++] != '\0')
		if (fd_called->remain[i] == '\n')
			j++;
	if (j == 0)
		fill_fd(fd, ret_read, fd_called);
	ft_strdel(&buffer);
}

static int			print_line(int *ret_read, t_file_read *fd_called,
																	char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (fd_called->remain[i] != '\0' && fd_called->remain[i] != '\n')
		i++;
	if (!(*line = ft_strndup(fd_called->remain, i)))
		return (-1);
	if (i == 0 && fd_called->remain[0] == '\n')
	{
		if (!(tmp = ft_strdup(&fd_called->remain[++i])))
			return (-1);
	}
	else
	{
		(fd_called->remain[i] == '\0' ? i = i - 1 : 0);
		if (!(tmp = ft_strdup(&fd_called->remain[i + 1])))
			return (-1);
	}
	ft_strdel(&fd_called->remain);
	if (tmp && ft_strlen(tmp) > 1)
		fd_called->remain = ft_strdup(tmp);
	ft_strdel(&tmp);
	(i >= 0 ? *ret_read = 1 : *ret_read);
	return (1);
}

static void			ft_free_lst(t_file_read **fd_save, int fd)
{
	t_file_read *current;
	t_file_read *prev;

	current = *fd_save;
	prev = *fd_save;
	while (current)
	{
		if (current->next && (current->next)->fd == fd)
			prev = current;
		if (current->fd == fd)
		{
			if (prev == *fd_save)
			{
				*fd_save = NULL;
			}
			else
				prev->next = current->next;
			free(current);
			current = NULL;
			break ;
		}
		current = current->next;
	}
}

int					get_next_line(const int fd, char **line)
{
	static	t_file_read	*fd_save = NULL;
	t_file_read			*fd_called;
	int					ret_read;
	size_t				i;

	if (BUFF_SIZE_GNL == 0 || !(line) || fd < 0)
		return (-1);
	ret_read = 1;
	i = 0;
	ft_search_fd(fd, &fd_save, &fd_called);
	while (fd_called->remain[i] != '\0' && fd_called->remain[i] != '\n')
		++i;
	if (ft_strlen(fd_called->remain) == 0 || i == ft_strlen(fd_called->remain))
		fill_fd(fd, &ret_read, fd_called);
	if (ret_read == -1)
		return (-1);
	if (ft_strlen(fd_called->remain) == 0 && ret_read == 0)
		ret_read = 0;
	if (ret_read >= 0 && print_line(&ret_read, fd_called, line) == -1)
		ret_read = -1;
	if (ret_read == -1 || fd_called->remain == NULL)
		ft_free_lst(&fd_save, fd_called->fd);
	return (ret_read);
}
