/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:03:56 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/21 16:36:31 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		ft_fill(t_filler *info, int m, int d, int *map)
{
	int i;
	int cl;

	i = 0;
	while (i < BSIZE)
	{
		if (map[i] == 0)
		{
			cl = i % BOARD_C;
			if (i - BOARD_C >= 0 && map[i - BOARD_C] == m)
				map[i] = d;
			if (i + BOARD_C < BSIZE && map[i + BOARD_C] == m)
				map[i] = d;
			if (cl - 1 >= 0 && map[i - 1] == m)
				map[i] = d;
			if (cl + 1 < BOARD_C && map[i + 1] == m)
				map[i] = d;
		}
		i++;
	}
}

static int		ft_check(t_filler *info, int *map)
{
	int i;

	i = 0;
	while (i < BSIZE)
	{
		if (map[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

void			ft_bomb(t_filler *info, char c, int *map, char *board)
{
	int i;
	int m;
	int d;

	i = 0;
	m = -1;
	d = 1;
	ft_bzero(map, 4 * BSIZE);
	while (i < BSIZE)
	{
		if (board[i] == c)
			map[i] = -1;
		i++;
	}
	while (ft_check(info, map) == 0)
	{
		ft_fill(info, m, d, map);
		(m == -1 ? m = 1 : m++);
		d++;
	}
}
