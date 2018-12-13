# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/24 06:17:23 by jocohen           #+#    #+#              #
#    Updated: 2018/12/12 16:42:08 by jocohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#	COLOR DISPLAY

NC = \033[0m
RED = \033[1;31m
GREEN = \033[0;32m
LOW_GREEN = \033[1;32m
BLUE = \033[1;34m
PURPLE = \033[0;35m
WHITE = \033[1;37m
YELLOW = \033[1;33m
CYAN = \033[0;36m
BLACK = \033[0;30m
DARK_GRAY = \033[1;30m



#	PERCENT DISPLAY

ifneq ($(words $(MAKECMDGOALS)),1)
.DEFAULT_GOAL = all

%:
	@$(MAKE) $@ --no-print-directory -rRf $(firstword $(MAKEFILE_LIST))
else
ifndef ECHO
T := $(shell $(MAKE) $(MAKECMDGOALS) --no-print-directory \
	-nrRf $(firstword $(MAKEFILE_LIST)) \
	ECHO="COUNTTHIS" | grep -c "COUNTTHIS")
N := x
C = $(words $N)$(eval N := x $N)
ECHO = echo -ne "\r $(DARK_GRAY)[$(PURPLE)`expr $C '*' 100 / $T`%$(DARK_GRAY)]$(NC)"
endif


#	CLASSIC MAKEFILE RULES/VAR

.PHONY: all, clean, fclean, re

NAME = 42sh

CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -Llibft
LDLIBS = -lft -ltermcap

INCLUDE = ./includes
PATH_LIB = ./libft/
PATH_SRC = ./
PATH_OBJ = ./obj/

NAME_SRC = shell.c \
		   env_analysis.c \
		   var_env_management.c \
		   lst_deletion.c \
		   ft_exit.c \
		   ft_realloc.c \
		   ft_writestdin.c \
		   set_term.c \
		   signal_control.c \
		   prompter.c \
		   prompter_stuff.c \
		   ending_input_line.c \
		   input_analysis.c \
		   escape_analysis.c \
		   execute_spe_keys.c \
		   execute_spe_keys2.c \
		   history_tree.c \
		   history_stuff.c \
		   history_movement.c \
		   cursor_fit.c \
		   cursor_shift.c \
		   selection_buffer.c \
		   paste_and_cut.c \
		   caller_display.c \
		   line_displays.c

NAME_OBJ = $(NAME_SRC:.c=.o)

SRC = $(addprefix $(PATH_SRC),$(NAME_SRC))
OBJ = $(addprefix $(PATH_OBJ),$(NAME_OBJ))

run:
	./42sh

all: $(NAME)

$(NAME): $(OBJ)
ifeq (,$(filter re ,$(MAKECMDGOALS)))
	@$(ECHO) "Linking $(LOW_GREEN)$@$(NC)"
endif
	@echo
	@make -C $(PATH_LIB)
	@gcc $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@
ifeq (,$(filter re ,$(MAKECMDGOALS)))
	@$(ECHO) "$(GREEN)$(NAME) Completed$(NC)"
else
	@echo " The attempt to compile $(WHITE)$(NAME)$(RED) succeed."
endif
	@echo

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
ifeq (,$(filter re ,$(MAKECMDGOALS)))
	@$(ECHO) "Compiling $(DARK_GRAY)$@$(NC)"
endif
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@gcc $(CFLAGS) -I $(INCLUDE) -o $@ -c $<


clean:
	@rm -f $(OBJ)
	@make clean -C $(PATH_LIB)
	@rmdir $(PATH_OBJ) 2> /dev/null || true

fclean: clean
	@echo
	@make fclean -C $(PATH_LIB)
	@rm -f $(NAME)
ifeq (,$(filter re ,$(MAKECMDGOALS)))
	@$(ECHO) Clean Done
else
	@echo "$(RED) PLEASE STAND BY "
	@echo
	@sleep 0.5
	@echo -n .
	@sleep 0.5
	@echo -n .
	@sleep 0.5
	@echo -n .
	@echo "\n"
	@echo " DISPLAY MALFUNCTIONNING "
endif

re: fclean all

debug : $(OBJ)
	@make -C $(PATH_LIB)
	@gcc $(CFLAGS) $(LDFLAGS) $(LDLIBS) -fsanitize=address -g3 $^ -o $(NAME)
	@echo "$(NAME) : DEBUG MODE"

endif
