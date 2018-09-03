/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 12:06:53 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/22 13:41:43 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static int		ft_player(t_filler *info)
{
	if (ft_strstr(LINE, "cpaquet.filler"))
	{
		if (LINE[10] != '1' && LINE[10] != '2')
		{
			ft_error("Error : Player");
			return (-1);
		}
		(LINE[10] == '1' ? ME = 'O' : 0);
		(LINE[10] == '1' ? ADV = 'X' : 0);
		(LINE[10] == '2' ? ME = 'X' : 0);
		(LINE[10] == '2' ? ADV = 'O' : 0);
	}
	else
		return (0);
	return (1);
}

static	int		ft_get_size(t_filler *info, char flag)
{
	if (flag == 'B')
	{
		BOARD_L = ft_atoi(&LINE[8]);
		BOARD_C = ft_atoi(ft_strchr(&LINE[8], ' '));
		if (BOARD_L <= 0 || BOARD_C <= 0)
			ft_error("Error : BOARD");
		if (!BOARD)
			if (!(BOARD = ft_strnew(BSIZE)))
				return (-1);
		if (!BOARD2)
			if (!(BOARD2 = ft_strnew(BSIZE)))
				return (-1);
	}
	else if (flag == 'P')
	{
		PIECE_L = ft_atoi(LINE + 6);
		PIECE_C = ft_atoi(ft_strchr(LINE + 6, ' '));
		if (PIECE_L <= 0 || PIECE_C <= 0)
			ft_error("Error : PIECE");
		if (!(PIECE = ft_strnew(PSIZE)))
			return (-1);
	}
	return (1);
}

static int		ft_get_board(t_filler *info)
{
	int		i;

	i = 0;
	while (ft_isdigit(LINE[0]))
	{
		if (ft_check_b_line(info) != 1 || i > BOARD_L)
		{
			ft_error("Error : BOARD");
			return (-1);
		}
		ft_strcpy(BOARD + (i * BOARD_C), LINE + 4);
		if (i == BOARD_L)
			break ;
		i++;
		ft_strdel(&LINE);
		get_next_line(0, &LINE);
	}
	if (i != BOARD_L)
	{
		ft_error("Error : BOARD");
		return (-1);
	}
	return (1);
}

static int		ft_get_piece(t_filler *info)
{
	int		i;

	i = 0;
	while (LINE[0] == '.' || LINE[0] == '*')
	{
		if (ft_check_p_line(info) == -1)
		{
			ft_error("Error : PIECE1");
			return (-1);
		}
		ft_strcpy(PIECE + (i * PIECE_C), LINE);
		i++;
		ft_strdel(&LINE);
		if (i == PIECE_L)
			break ;
		get_next_line(0, &LINE);
	}
	if (i != PIECE_L)
	{
		ft_error("Error : PIECE2");
		return (-1);
	}
	return (1);
}

int				ft_get_info(t_filler *info)
{
	while (get_next_line(0, &LINE) > 0)
	{
		if (ft_player(info) == -1)
			return (-1);
		if (ft_strstr(LINE, "Plateau") != NULL)
			if (ft_get_size(info, 'B') == -1)
				return (-1);
		if (ft_isdigit(LINE[0]) == 1)
			if (ft_get_board(info) == -1)
				return (-1);
		if (ft_strstr(LINE, "Piece") != NULL)
			if (ft_get_size(info, 'P') == -1)
				return (-1);
		if (LINE[0] == '.' || LINE[0] == '*')
		{
			if (ft_get_piece(info) == 1)
				break ;
			else
				return (-1);
		}
		ft_strdel(&LINE);
	}
	if (ME == 0 || !BOARD || !BOARD2 || !PIECE || PIECE_L == 0 || BOARD_L == 0)
		return (-1);
	return (1);
}
