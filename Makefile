# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/16 13:17:30 by rcochran          #+#    #+#              #
#    Updated: 2025/04/24 10:59:04 by rcochran         ###   ########.fr        #

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

FILES		= 	builtin/builtin_cd\
				builtin/builtin_echo\
				builtin/builtin_env\
				builtin/builtin_exit\
				builtin/builtin_export\
				builtin/builtin_pwd\
				builtin/builtin_unset\
				builtin/builtin_utils\
				exec/exec_cmd\
				exec/exec_heredoc\
				exec/exec_pipe\
				exec/exec_redir\
				exec/exec_tree\
				exec/exec_utils\
				lexing/backslash \
				lexing/lexer_utils \
				lexing/lexer \
				lexing/operator \
				lexing/quote \
				lexing/redirection \
				lexing/token\
				parsing/cmd \
				parsing/debug_display \
				parsing/is_closed \
				parsing/parse_cmd \
				parsing/parse_heredoc \
				parsing/parse_rd_file \
				parsing/parse_utils \
				parsing/parse \
				clear \
				init \
				minishell_cleaner \
				prompt \
				set_env \
				tree_builder \
				tree_builder_utils

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
	mkdir -p $(OBJ_DIR)/builtin
	mkdir -p $(OBJ_DIR)/lexing
	mkdir -p $(OBJ_DIR)/parsing
	mkdir -p $(OBJ_DIR)/exec

debug : all