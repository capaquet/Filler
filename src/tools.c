/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 13:14:58 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/22 13:48:06 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		ft_error(char *msg)
{
	ft_printf("%w%s", 2, msg);
}

int			ft_check_b_line(t_filler *info)
{
	int				i;
	static int		nbr_line = 0;
	static int		nbr_x = 0;
	static int		nbr_o = 0;

	i = 4;
	while (LINE[i])
	{
		if (LINE[i] != '.' && LINE[i] != 'X' && LINE[i] != 'O')
			return (-1);
		if (LINE[i] == 'X')
			nbr_x++;
		if (LINE[i] == 'O')
			nbr_o++;
		i++;
	}
	nbr_line++;
	if (BOARD_C != i - 4)
		return (-1);
	if (nbr_line == BOARD_L && (nbr_x == 0 || nbr_o == 0))
		return (-1);
	return (1);
}

int			ft_check_p_line(t_filler *info)
{
	int				i;
	static int		nbr_line = 0;
	static	int		nbr_star = 0;

	i = 0;
	while (LINE[i])
	{
		if (LINE[i] != '.' && LINE[i] != '*')
			return (-1);
		if (LINE[i] == '*')
			nbr_star++;
		i++;
	}
	nbr_line++;
	if (i != PIECE_C)
		return (-1);
	if (nbr_line == PIECE_L && nbr_star == 0)
		return (-1);
	return (1);
}

void		ft_sort_tab_indexed(int *tab, int size)
{
	int		i;
	int		tmp;

	i = 0;
	tmp = 0;
	while (i <= size - 3)
	{
		if (tab[i + 1] > tab[i + 3])
		{
			tmp = tab[i + 1];
			tab[i + 1] = tab[i];
			tab[i] = tab[i + 2];
			tab[i + 2] = tab[i + 1];
			tab[i + 1] = tab[i + 3];
			tab[i + 3] = tmp;
			i = 0;
		}
		else
			i += 2;
	}
	return ;
}

void		ft_crop(t_filler *info)
{
	int		i;

	i = 0;
	P_L_MIN = 1234567890;
	P_CL_MIN = 1234567890;
	while (PIECE[i])
	{
		if (PIECE[i] == '*')
		{
			if (i / PIECE_C < P_L_MIN)
				P_L_MIN = i / PIECE_C;
			if (i % PIECE_C < P_CL_MIN)
				P_CL_MIN = i % PIECE_C;
		}
		i++;
	}
}
