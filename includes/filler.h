/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/14 11:47:17 by cpaquet           #+#    #+#             */
/*   Updated: 2018/03/22 14:14:29 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "libft.h"

# define LINE				info->line

# define BOARD				info->board
# define BOARD2				info->board2
# define BOARD_C			info->board_columns
# define BOARD_L			info->board_lines
# define BSIZE				BOARD_C * BOARD_L

# define PIECE				info->piece
# define PIECE_C			info->piece_columns
# define PIECE_L			info->piece_lines
# define P_L_MIN			info->piece_line_min
# define P_CL_MIN			info->piece_cl_min
# define PSIZE				PIECE_L * PIECE_C

# define I					info->index_board

# define MME				info->matrice_me
# define MADV				info->matrice_adv

# define OPTIONS_L			info->options_list
# define OPTIONS_I			info->options_index
# define OPTIONS_N			200

# define ME					info->me
# define ADV				info->adv

typedef struct	s_filler
{
	char	*line;

	char	*board;
	char	*board2;
	int		board_columns;
	int		board_lines;

	char	*piece;
	int		piece_columns;
	int		piece_lines;
	int		piece_line_min;
	int		piece_cl_min;

	int		index_board;

	int		*matrice_me;
	int		*matrice_adv;

	int		*options_list;
	int		options_index;

	char	me;
	char	adv;
}				t_filler;

int				ft_get_info(t_filler *info);
int				ft_check_b_line(t_filler *info);
int				ft_check_p_line(t_filler *info);
void			ft_bomb(t_filler *info, char c, int *map, char *board);
void			ft_crop(t_filler *info);
int				ft_placement(t_filler *info);
void			ft_error(char *msg);
void			ft_sort_tab_indexed(int *tab, int size);

#endif
