# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbikoumo <gbikoumo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/26 17:11:30 by santa             #+#    #+#              #
#    Updated: 2019/10/03 00:12:43 by gbikoumo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rc
RM = rm -rf

LIBFT = libft
INCDIR = includes
OBJDIR = objects
SRCDIR = sources

SOURCES = 	ft_printf.c \
			string.c \
			octal.c \
			hexa.c \
			unsigned.c \
			integer.c \
			float.c \
			parsing.c \
			color.c \
			binary.c 
			
INC = ft_printf.h

SRCS = $(addprefix $(SRCDIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJDIR)/, $(SOURCES:.c=.o))


all : $(OBJDIR) $(NAME)

$(NAME) : $(INCDIR)/$(INC) $(OBJS) 
	make -C libft
	cp libft/libft.a ./$(NAME)
	$(AR) $(NAME) $(OBJS)
	ranlib $(NAME)

$(OBJDIR) :
	mkdir -p objects

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

clean :
	$(RM) $(OBJS)
	make -C libft clean

fclean : clean
	$(RM) $(NAME)
	make -C libft fclean

re : fclean all

test : all
	$(CC) $(CFLAGS) main.c -L. -lftprintf -o exectest

