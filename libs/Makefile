# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fsuomins <fsuomins@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 00:31:29 by fsuomins          #+#    #+#              #
#    Updated: 2023/08/19 00:03:52 by fsuomins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all

## COLORS DEFINITIONS

red:=$(shell tput setaf 1)
green:=$(shell tput setaf 2)
yellow:=$(shell tput setaf 3)
blue:=$(shell tput setaf 4)
purple:=$(shell tput setaf 5)
cyan:=$(shell tput setaf 6)
white:=$(shell tput setaf 7)
reset:=$(shell tput sgr0)

color:
	@make -s _color-test

_color-test:
	$(info $(red)Message$(reset))
	$(info $(green)Message$(reset))
	$(info $(yellow)Message$(reset))
	$(info $(blue)Message$(reset))
	$(info $(purple)Message$(reset))
	$(info $(cyan)Message$(reset))
	$(info $(white)Message$(reset))

# PATHS

SRC_PATH = .
TEST_PATH = tests
PATH_INC = ./

# FILES

NAME = libft.a
FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
		ft_strlen ft_memset ft_tolower ft_toupper ft_bzero \
		ft_calloc ft_memchr ft_memcpy ft_memmove ft_strlcpy \
		ft_tolower ft_toupper ft_strlcat ft_strchr ft_strncmp \
		ft_strrchr ft_memcmp ft_strnstr ft_atoi ft_strdup ft_substr \
		ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
		ft_putchar_fd ft_islower ft_isupper ft_strtok ft_strcmp \
		ft_putstr_fd
		
SRCS = $(addprefix $(SRC_PATH)/, $(addsuffix .c, $(FILES)))
OBJS := ${SRCS:.c=.o}

# FLAGS

CC = cc
CFLAGS = -Wall -Wextra -Werror

# TARGETS

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

valgrind:
	valgrind --track-origins=yes --error-exitcode=42 --leak-check=full --show-leak-kinds=all --quiet ./test

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re