# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 13:17:30 by rcochran          #+#    #+#              #
#    Updated: 2025/04/16 13:30:34 by rcochran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra -lreadline
AR			=	ar -rcs
NAME		= 	minishell

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

INCLUDES	= -I$(LIBFT_PATH)/includes

FILES		= 
SRC_DIR		= 	src/
SRC_FILES	=	$(addsuffix .c, $(FILES))
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

MAIN		=	main.c
OBJ_DIR		= obj/
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_MAIN	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_DIR)$(MAIN))


all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re : fclean all

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(SRC_DIR)$(MAIN) -L$(LIBFT_PATH) -lft

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

debug : $(LIBFT) $(OBJ_DIR) $(OBJ) Makefile
	$(CC) -g3 $(CFLAGS) $(OBJ) $(OBJ_MAIN) -L$(LIBFT_PATH) -lft -o $(NAME)

