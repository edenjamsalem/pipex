# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 14:04:43 by eamsalem          #+#    #+#              #
#    Updated: 2024/06/24 12:17:37 by eamsalem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CFLAGS = -Wall -Werror -Wextra -g3

OBJDIR = ./build
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a

SRCS =	pipex.c \
		check_fns.c \
		pipe_fns.c

all: $(OBJDIR) $(NAME) $(LIBFT)

$(OBJDIR)/%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJDIR) $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR) all

clean:
	make -C $(LIBFTDIR) clean
	rm -fr $(OBJDIR)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -fr $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
