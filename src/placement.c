/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 10:30:34 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/21 19:36:15 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		ft_influence(t_filler *info, char inf)
{
	I = 0;
	if (inf == 0)
		while (I < BSIZE)
		{
			if (MADV[I] == -1 || MME[I] == -1)
				MME[I] = 0;
			else
				MME[I] = MADV[I] - MME[I];
			I++;
		}
	else if (inf == 1)
		while (I < BSIZE)
		{
			if (MADV[I] == -1 || MME[I] == -1 || MADV[I] - MME[I] == 0)
				MME[I] = 0;
			else if (MADV[I] - MME[I] < 0)
				MME[I] = -1;
			else if (MADV[I] - MME[I] > 0)
				MME[I] = 1;
			I++;
		}
}

static int		ft_check_place(t_filler *info)
{
	int		i;
	int		k;
	int		m;

	i = P_L_MIN * PIECE_C + P_CL_MIN;
	k = 0;
	m = 0;
	while (i < PSIZE)
	{
		m = I + (i % PIECE_C - P_CL_MIN) + ((i / PIECE_C - P_L_MIN) * BOARD_C);
		if (PIECE[i] == '*')
		{
			if (m > BSIZE - 1 || ((I % BOARD_C) + (i % PIECE_C) > BOARD_C - 1))
				return (0);
			if (BOARD[m] == ADV)
				return (0);
			if (BOARD[m] == ME)
				k++;
		}
		i++;
	}
	if (k != 1)
		return (0);
	return (1);
}

static void		ft_options(t_filler *info)
{
	int		i;
	int		tmp;

	i = P_L_MIN * PIECE_C + P_CL_MIN;
	tmp = 0;
	while (i < PSIZE)
	{
		if (PIECE[i] == '*')
			tmp += MME[I + (i % PIECE_C - P_CL_MIN) +
			((i / PIECE_C - P_L_MIN) * BOARD_C)];
		i++;
	}
	ft_sort_tab_indexed(OPTIONS_L, OPTIONS_N);
	i = OPTIONS_N - 1;
	while (i >= 1)
	{
		if (tmp < OPTIONS_L[i])
		{
			OPTIONS_L[i] = tmp;
			OPTIONS_L[i - 1] = I;
			break ;
		}
		i -= 2;
	}
}

static void		ft_score(t_filler *info, int option_index)
{
	int		i;
	int		m;
	int		tmp;

	m = 0;
	i = P_L_MIN * PIECE_C + P_CL_MIN;
	ft_strcpy(BOARD2, BOARD);
	while (i < PSIZE)
	{
		m = option_index + (i % PIECE_C - P_CL_MIN) +
		((i / PIECE_C - P_L_MIN) * BOARD_C);
		if (PIECE[i] == '*')
			BOARD2[m] = ME;
		i++;
	}
	ft_bomb(info, ME, MME, BOARD2);
	ft_influence(info, 1);
	i = 0;
	tmp = 0;
	while (i < BSIZE)
		tmp += MME[i++];
	OPTIONS_L[OPTIONS_I + 1] = tmp;
}

int				ft_placement(t_filler *info)
{
	ft_influence(info, 0);
	I = 1;
	while (I < BSIZE)
	{
		if (ft_check_place(info) == 1)
		{
			ft_options(info);
		}
		I++;
	}
	ft_sort_tab_indexed(OPTIONS_L, OPTIONS_N);
	OPTIONS_I = 0;
	while (OPTIONS_I < OPTIONS_N - 1 && OPTIONS_L[OPTIONS_I] != 1234567890)
	{
		ft_score(info, OPTIONS_L[OPTIONS_I]);
		OPTIONS_I += 2;
	}
	ft_sort_tab_indexed(OPTIONS_L, OPTIONS_N);
	OPTIONS_I = OPTIONS_N - 1;
	while (OPTIONS_L[OPTIONS_I] == 1234567890)
		OPTIONS_I -= 2;
	if (OPTIONS_I < 0)
		return (0);
	I = OPTIONS_L[OPTIONS_I - 1];
	return (1);
}
