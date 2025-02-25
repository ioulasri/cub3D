# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imoulasr <imoulasr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 12:08:46 by imoulasr          #+#    #+#              #
#    Updated: 2025/02/25 16:12:05 by imoulasr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

NAME = cub3D

CC = cc
CFLAGS = -Werror -Wextra -Wall -fsanitize=address -g3

MLX_PATH = minilibx-linux/
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)$(MLX_NAME)

LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

GNL_PATH = get_next_line/
GNL_SRC = get_next_line.c get_next_line_utils.c
GNL_OBJ = $(GNL_SRC:.c=.o)
GNL = $(addprefix $(OBJ_PATH), $(GNL_OBJ))

SRC_PATH = ./src/
SRC = main.c \
	  parsing/read_file_map.c \
	  parsing/read_file_map_utils.c \
	  parsing/parse.c \
	  parsing/parse_utils.c \
	  parsing/get_map.c \
	  parsing/get_textures.c \
	  parsing/valid_map_file.c \
	  parsing/map.c \
	  parsing/get_colors.c \
	  free/free_config.c \
	  free/free_file_map.c \
	  free/others.c \
	  utils/remove_nl.c \

SRCS = $(addprefix $(SRC_PATH), $(SRC))

OBJ_PATH = ./objects/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I ./includes/ \
      -I ./libft/ \
      -I ./minilibx-linux/ \
      -I ./get_next_line/

all: $(OBJ_PATH) $(MLX) $(LIBFT) $(GNL) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)/parsing
	mkdir -p $(OBJ_PATH)/rendering
	mkdir -p $(OBJ_PATH)/free
	mkdir -p $(OBJ_PATH)/utils

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJ_PATH)%.o: $(GNL_PATH)%.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS) $(GNL)
	$(CC) $(CFLAGS) $(OBJS) $(GNL) -o $@ $(INC) $(LIBFT) $(MLX) -lXext -lX11 -lm

$(LIBFT):
	make -sC $(LIBFT_PATH)

$(MLX):
	make -sC $(MLX_PATH)

clean:
	rm -rf $(OBJ_PATH)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	rm -f $(GNL)

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all
