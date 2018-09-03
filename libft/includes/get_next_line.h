/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 13:50:20 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/22 11:01:41 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE_GNL 1

# include "libft.h"

typedef struct	s_file_read
{
	int					fd;
	char				*remain;
	struct s_file_read	*next;
}				t_file_read;

int				get_next_line(const int fd, char **line);

#endif
