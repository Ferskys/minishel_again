# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aqueiroz <aqueiroz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 09:18:52 by aqueiroz          #+#    #+#              #
#    Updated: 2023/09/14 11:15:55 by aqueiroz         ###   ########.fr        #
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
	@$(MAKE) -s _color-test

_color-test:
	$(info $(red)Message$(reset))
	$(info $(green)Message$(reset))
	$(info $(yellow)Message$(reset))
	$(info $(blue)Message$(reset))
	$(info $(purple)Message$(reset))
	$(info $(cyan)Message$(reset))
	$(info $(white)Message$(reset))

# MANDATORY FILES

NAME = minishell

SRC_PATH = srcs
UTILS_PATH = utils
LIB_PATH = libs
OBJ_PATH = objs
PATH_INC = includes

FILES  = 	minishell

FILES += 	states/init \
			states/prompt \
			states/parse \
			states/execute \
			states/exit

FILES += 	init/signals \
			init/create_env 

FILES +=	prompt/print_prompt \
			prompt/validate_prompt
			
FILES += 	parse/expand_exit \
			parse/replace_variables \
			parse/expand_var \
			parse/expand_tilde \
			parse/quotes \
			parse/spaces \
			parse/split_string \
			parse/tokens \
			parse/invalid_redirects
			
FILES += 	execute/args \
			execute/clear_exec \
			execute/com \
			execute/children \
			execute/command \
			execute/env \
			execute/get_info \
			execute/input \
			execute/multi_cmd \
			execute/one_cmd \
			execute/output \
			execute/redirects/heredoc \
			execute/redirects/redirects \
			execute/redirects/output \
			execute/redirects/expansions \
			execute/redirects/create_redirects \
			execute/env/envs \
			execute/builtin/cd \
			execute/builtin/echo \
			execute/builtin/env \
			execute/builtin/exit \
			execute/builtin/export \
			execute/builtin/pwd \
			execute/builtin/unset

FILES_U += 	data \
			free \
			envs \
			vars \
			spaces \
			tokens \
			types \
			cd \
			cd2 \
			heredoc \
			redirect \
			tok \
			clear_data

UTILS = $(addprefix $(UTILS_PATH)/, $(addsuffix .c, $(FILES_U)))
SRCS  = $(addprefix $(SRC_PATH)/, $(addsuffix .c, $(FILES)))
OBJS  = $(SRCS:.c=.o)
OBJS  += $(UTILS:.c=.o)

# FLAGS

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LIBFLAGS = -L./$(LIB_PATH) -lft -lreadline 

all: $(NAME)

LIBFT:
	@$(MAKE) -s -k -C $(LIB_PATH)

$(NAME): LIBFT $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIBFLAGS) -o $@
	$(info $(purple)Project compiled. Run './$(NAME)' to start.$(reset))

valgrind:
	make
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes \
	--suppressions=./readline.supp --leak-check=full \
	--show-leak-kinds=all --trace-children-skip='*/bin/*,*/sbin/*' --quiet ./minishell
clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIB_PATH) --silent clean
	$(info $(yellow)All object files were removed.$(reset))

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIB_PATH) --silent fclean
	$(info $(yellow)Executables files were removed.$(reset))

re: fclean all
	
.PHONY: all color clean fclean re valgrind