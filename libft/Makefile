# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcochran <rcochran@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 17:15:49 by rcochran          #+#    #+#              #
#    Updated: 2025/04/18 17:26:03 by rcochran         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re

CC= cc
CFLAGS= -Wall -Wextra -Werror
SRC_DIR = src/
SRC_FILES = $(addsuffix .c, $(FILES))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
FILES :=	ft_atoi \
			ft_atoi_base \
			ft_bzero \
			ft_calloc \
			ft_convert_base \
			ft_isalnum \
			ft_isalpha \
			ft_isascii \
			ft_isdigit \
			ft_isprint \
			ft_itoa \
			ft_memchr \
			ft_memcmp \
			ft_memcpy \
			ft_memmove \
			ft_memset \
			ft_putchar_fd \
			ft_putendl_fd \
			ft_putnbr_fd \
			ft_putstr_fd \
			ft_realloc \
			ft_split \
			ft_strchr \
			ft_strdup \
			ft_striteri \
			ft_strjoin \
			ft_strlcat \
			ft_strlcpy \
			ft_strlen \
			ft_strmapi \
			ft_strncmp \
			ft_strndup \
			ft_strnstr \
			ft_strrchr \
			ft_strtrim \
			ft_substr \
			ft_tolower \
			ft_toupper \
			get_next_line \
			ft_lstnew_bonus \
			ft_lstadd_front_bonus \
			ft_lstsize_bonus \
			ft_lstlast_bonus \
			ft_lstadd_back_bonus \
			ft_lstdelone_bonus \
			ft_lstclear_bonus \
			ft_lstiter_bonus \
			ft_lstmap_bonus \
			ft_print_hexa \
			ft_print_num \
			ft_print_ptr \
			ft_printf_utils \
			ft_printf \
			ft_swap

NAME := libft.a
HEADER := includes/
OBJ			=	$(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))
OBJ_DIR = obj/

all : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

$(NAME): $(OBJ_DIR) $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(HEADER) -o $@ -c $<


$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

#unit : all
#make my own libft tester

main : all
	$(CC) main.c -c -I$(HEADER) -o obj/main.o
	$(CC) obj/main.o -L. -l:libft.a -o obj/a.out
