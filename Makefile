# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntom <ntom@student.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/30 16:32:31 by ntom              #+#    #+#              #
#    Updated: 2019/08/01 14:59:15 by ntom             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
CC = gcc
CFLAGS += -fsanitize=address -Wall -Wextra -Werror -I includes
LIBDIR = libft

SRC = main.c parsing.c binary_tree.c option_l.c aff_del_tree.c column.c

O_FILES = $(SRC:%.c=%.o)
FLAGLIB = -L$(LIBDIR) -lft

all: $(NAME)

$(NAME): $(O_FILES)
	@make all -C $(LIBDIR)
	@gcc $(CFLAGS) $(FLAGLIB) -o $(NAME) $(O_FILES)

clean:
	@/bin/rm -rf $(O_FILES)
	@make clean -C $(LIBDIR)

fclean: clean
	@/bin/rm -rf $(NAME)
	@make fclean -C $(LIBDIR)

lib:
	@make re -C $(LIBDIR)

norm:
	@norminette $(SRC)

normlib:
	@norminette $(LIBDIR)/*.c

re: fclean all

.PHONY: all fclean clean re
