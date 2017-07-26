# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heynard <heynard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/06/08 15:38:42 by heynard           #+#    #+#              #
#    Updated: 2017/06/27 20:26:37 by heynard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select

CC = gcc

FLAGS = -Wall -Wextra -Werror -ltermcap

FLAGS_LFT = -L ./libft/ -lft

PATH_SRCS = ./srcs/

SRC_FILES = main.c\
			fts_shell.c\
			fts_parser.c\
			fts_runtermconfig.c\
			fts_display.c\
			fts_handle_event.c\
			fts_signal_handler.c\
			fts_move.c\
			fts_display_feature.c\
			fts_putname.c\
			fts_parse_rep.c

SRCS = $(addprefix $(PATH_SRCS), $(SRC_FILES))

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./libft/
	@$(CC) $(FLAGS) $(FLAGS_LFT) $^ -o $(NAME)
	@echo "\033[1;34mft_select\t\033[1;33mBuilding\t\t\033[0;32m[OK]\033[0m"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: all clean fclean re

clean:
	@make -C ./libft/ clean
	@rm -f $(OBJ)
	@echo "\033[1;34mft_select\t\033[1;33mCleaning objects\t\033[0;32m[OK]\033[0m"

fclean: clean
	@make -C ./libft/ fclean
	@rm -f $(NAME)
	@echo "\033[1;34mft_select\t\033[1;33mCleaning ft_select\t\033[0;32m[OK]\033[0m"

re: fclean all
