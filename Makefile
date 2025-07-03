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

.PHONY : all clean fclean re debug quiet

# Comment next line to show directories
MAKEFLAGS += --no-print-directory
# QUIET = @ -> mutes make cmd in terminal, remove @ to show again
QUIET		=	@

CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra -MMD -MP
AR			=	ar -rcs
NAME		= 	minishell

UNAME_S 	:= $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	READLINE_DIR := $(shell brew --prefix readline)
	INCLUDES += -I$(READLINE_DIR)/include
	READLINE_LIBS := -L$(READLINE_DIR)/lib -lreadline -lncurses
else
	READLINE_LIBS := -lreadline
endif



LIBFT_PATH	=	./libft
LIBFT		=	$(LIBFT_PATH)/libft.a

INCLUDES	= 	-I$(LIBFT_PATH)/includes\
				-I ./includes\
				-I$(READLINE_DIR)/include

FILES		= 	builtin/builtin_cd\
				builtin/builtin_echo\
				builtin/builtin_env\
				builtin/builtin_exit\
				builtin/builtin_export\
				builtin/builtin_pwd\
				builtin/builtin_unset\
				builtin/builtin_utils\
				exec/exec_cmd\
				exec/exec_cmd_init\
				exec/exec_cmd_utils\
				exec/exec_heredoc\
				exec/exec_heredoc_init \
				exec/exec_heredoc_init2 \
				exec/exec_pipe\
				exec/exec_redir\
				exec/exec_tree\
				exec/exec_utils\
				expand/chunk \
				expand/exp_cmd_args \
				expand/expand_heredocs \
				expand/expand_path \
				expand/expand_str \
				expand/expand_utils \
				expand/expand_wildcard \
				expand/variable \
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
				signal/signal_handler \
				signal/signal_listener \
				common_utils\
				init \
				minishell_cleaner \
				prompt \
				set_env \
				sort_tokens \
				tree_builder \
				tree_builder_utils \
				tree_builder_utils2

SRC_DIR		= 	src/
SRC_FILES	=	$(addsuffix .c, $(FILES))
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

MAIN		=	main.c
OBJ_DIR		= 	obj/
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_MAIN	=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC_DIR)$(MAIN))

ifneq ($(filter debug, $(MAKECMDGOALS)),)
CFLAGS += -g3
endif

all : $(NAME)
	@ echo "ft_palourde minishell is ready !"
	@ cat assets/ms_ascii

clean :
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re : fclean all

# $(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ) $(OBJ_MAIN)
# 	$(QUIET) $(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(OBJ_MAIN) -L$(LIBFT_PATH) -lft -lreadline -o $(NAME)
$(NAME) : $(LIBFT) $(OBJ_DIR) $(OBJ) $(OBJ_MAIN)
	$(QUIET) $(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(OBJ_MAIN) -L$(LIBFT_PATH) -lft $(READLINE_LIBS) -o $(NAME)

$(LIBFT):
	$(QUIET) make all -C $(LIBFT_PATH) 

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(QUIET) $(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR) : 
	$(QUIET) mkdir -p $(OBJ_DIR)
	$(QUIET) mkdir -p $(OBJ_DIR)/builtin
	$(QUIET) mkdir -p $(OBJ_DIR)/lexing
	$(QUIET) mkdir -p $(OBJ_DIR)/parsing
	$(QUIET) mkdir -p $(OBJ_DIR)/signal
	$(QUIET) mkdir -p $(OBJ_DIR)/exec
	$(QUIET) mkdir -p $(OBJ_DIR)/expand

debug : all