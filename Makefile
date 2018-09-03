# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acauchy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/29 10:04:49 by acauchy           #+#    #+#              #
#    Updated: 2018/03/22 12:59:17 by cpaquet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re LIB

NAME = cpaquet.filler

CC =			gcc
CFLAGS = 		-Wall -Wextra -Werror
CPPFLAG =		-I./includes -I./libft/includes

SRC_PATH = 		src
SRC_NAME =		main.c \
				get_info.c \
				bomb.c \
				placement.c \
				tools.c \

OBJ_PATH =		objs
OBJ_NAME =		$(SRC_NAME:.c=.o)
OBJ =			$(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LIBFT_PATH =	./libft

all: $(NAME)

$(NAME): LIB $(OBJ)
	@ echo "\x1B[032m" "-= Objs $(NAME) OK =-" "\x1B[0m"
	@ $(CC) $(OBJ) -L$(LIBFT_PATH) -lft -o $(NAME)
	@ echo "\x1B[032m" "-= $(NAME) OK =-" "\x1B[0m"

LIB:
	@ make -C $(LIBFT_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@ mkdir -p $(OBJ_PATH)
	@ $(CC) -c $(CFLAGS) $(CPPFLAG) $^ -o $@

clean:
	@ rm -Rf $(OBJ_PATH)
	@ echo "\x1B[031m" "-= Objs $(NAME) deleted =-" "\x1B[0m"
	@ make -C $(LIBFT_PATH) clean

fclean: clean
	@ make -C $(LIBFT_PATH) fclean
	@ rm -f $(NAME)
	@ echo "\x1B[031m" "-= $(NAME) deleted =-" "\x1B[0m"

re: fclean all
