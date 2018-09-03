/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:40:27 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/22 14:14:49 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		ft_free(t_filler *info)
{
	if (PIECE)
		ft_strdel(&PIECE);
	if (BOARD)
		ft_strdel(&BOARD);
	if (BOARD2)
		ft_strdel(&BOARD2);
	if (LINE)
		ft_strdel(&LINE);
	if (MME)
		free(MME);
	MME = NULL;
	if (MADV)
		free(MADV);
	MADV = NULL;
	if (OPTIONS_L)
		free(OPTIONS_L);
	OPTIONS_L = NULL;
}

static int		ft_init_matrice(t_filler *info)
{
	if (!MME)
		if (!(MME = (int*)malloc(sizeof(int) * (BSIZE))))
			return (-1);
	if (!MADV)
		if (!(MADV = (int*)malloc(sizeof(int) * (BSIZE))))
			return (-1);
	if (!OPTIONS_L)
		if (!(OPTIONS_L = (int*)malloc(sizeof(int) * OPTIONS_N)))
			return (-1);
	ft_bzero(MME, BSIZE * 4);
	ft_bzero(MADV, BSIZE * 4);
	I = 0;
	while (I < OPTIONS_N)
		OPTIONS_L[I++] = 1234567890;
	return (1);
}

int				main(void)
{
	t_filler	info;
	int			ret_line;
	int			ret_cl;

	ft_bzero(&info, sizeof(t_filler));
	while (1)
	{
		if (ft_get_info(&info) == -1)
			break ;
		if (ft_init_matrice(&info) == -1)
			break ;
		ft_crop(&info);
		ft_bomb(&info, info.me, info.matrice_me, info.board);
		ft_bomb(&info, info.adv, info.matrice_adv, info.board);
		if (ft_placement(&info) == 0)
			break ;
		ft_free(&info);
		ret_line = info.index_board / info.board_columns - info.piece_line_min;
		ret_cl = info.index_board % info.board_columns - info.piece_cl_min;
		ft_printf("%w%d %d\n", 1, ret_line, ret_cl);
	}
	ft_free(&info);
	ft_printf("%w0 0\n", 1);
	return (0);
}
