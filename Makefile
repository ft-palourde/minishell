# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 13:17:30 by rcochran          #+#    #+#              #
#    Updated: 2025/04/21 15:34:58 by rcochran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re debug

CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra -MMD -MP
AR			=	ar -rcs
NAME		= 	minishell

LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

INCLUDES	= 	-I$(LIBFT_PATH)/includes\
				-I ./includes

FILES		= 	builtin_cd\
				builtin_echo\
				builtin_env\
				builtin_exit\
				builtin_export\
				builtin_pwd\
				builtin_unset\
				lexer_utils \
				lexer \
				operator \
				parse \
				prompt \
				token\
				set_env
				
SRC_DIR		= 	src/
SRC_FILES	=	$(addsuffix .c, $(FILES))
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

MAIN		=	main.c
OBJ_DIR		= 	obj/
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_MAIN	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_DIR)$(MAIN))

ifneq ($(filter debug, $(MAKECMDGOALS)),)
CFLAGS += -g -v
endif

all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re : fclean all

$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(OBJ_MAIN) -L$(LIBFT_PATH) -lft -lreadline -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR) : 
	mkdir -p $(OBJ_DIR)

debug : all
