# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wbelfatm <wbelfatm@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/21 10:21:18 by wbelfatm          #+#    #+#              #
#    Updated: 2024/08/04 11:05:29 by wbelfatm         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror -Ofast # -fsanitize=address -g 
CC = cc
RM = rm -f

SRCS = main.c hooks.c draw.c raycasting.c utils.c rendering.c
OBJS = ${SRCS:.c=.o}
LIBMLX = ./lib/MLX42
GLFW = /goinfre/wbelfatm/homebrew/Cellar/glfw/3.4/lib
# GLFW = /opt/homebrew/Cellar/glfw/3.4/lib
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -L$(GLFW) -lm
INCLUDES = -I $(LIBMLX)
NAME = cub3d
HEADERS = cub3d.h $(LIBMLX)/MLX42.h

all: libmlx $(NAME)

%.o: %.c $(HEADERS) 
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) $(INCLUDES) -o $(NAME)

clean: 
	$(RM) $(OBJS)
	$(RM) -r $(LIBMLX)/build

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean, fclean, all, re, libmlx
	