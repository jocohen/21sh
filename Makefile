# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/26 16:54:18 by tcollard          #+#    #+#              #
#    Updated: 2018/10/18 19:05:17 by tcollard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, debug, norme

NAME = 21sh

END = \x1b[0m
GREEN = \x1b[32m

CFLAGS = -Wall -Werror -Wextra -g3
LDFLAGS = -Llibft
LDLIBS = -lft -ltermcap

PATH_LEXER = lexer/
PATH_PROMPT = prompt/
PATH_TOOLS = tools/
PATH_PARSER = parser/
PATH_BUILT = builtins/
PATH_ERROR = error/
PATH_TERMCAPS = termcaps/

INCLUDE = ./includes
PATH_LIB = ./libft/
PATH_SRC = ./srcs/
PATH_OBJ = ./obj/

SRC =	$(PATH_LEXER)check_closing_quote.c \
		$(PATH_LEXER)ft_splitwhitespace_shell.c \
		$(PATH_LEXER)ft_strsplit_shell.c \
		$(PATH_LEXER)replace_quote.c \
		$(PATH_LEXER)check_cmd_pipe.c \
		$(PATH_LEXER)lexer.c \
		$(PATH_PARSER)parser.c \
		$(PATH_PARSER)analyzer.c \
		$(PATH_PARSER)fill_ast.c \
		$(PATH_PARSER)analyzer_tools.c \
		$(PATH_BUILT)dispatch_builtins.c \
		$(PATH_BUILT)echo.c \
		$(PATH_BUILT)env.c \
		$(PATH_TOOLS)lexer_tools.c \
		$(PATH_TOOLS)split_tools.c \
		$(PATH_TOOLS)quote_tools.c \
		$(PATH_TOOLS)lst_tools.c \
		$(PATH_TOOLS)parser_tools.c \
		$(PATH_PROMPT)minishell.c \
		$(PATH_PROMPT)quote_prompt.c \
		$(PATH_ERROR)error.c \
		$(PATH_TERMCAPS)shell.c \
		$(PATH_TERMCAPS)prompter.c \
		$(PATH_TERMCAPS)caller_display.c \
		$(PATH_TERMCAPS)env_analysis.c \
		$(PATH_TERMCAPS)escape_analysis.c \
		$(PATH_TERMCAPS)ft_exit.c \
		$(PATH_TERMCAPS)ft_realloc.c \
		$(PATH_TERMCAPS)ft_writestdin.c \
		$(PATH_TERMCAPS)set_term.c \
		$(PATH_TERMCAPS)var_env_management.c \
		$(PATH_TERMCAPS)lst_deletion.c \
		$(PATH_TERMCAPS)eol_work.c \
		$(PATH_TERMCAPS)signal_control.c \
		$(PATH_TERMCAPS)historic_move.c \
		$(PATH_TERMCAPS)history_stuff.c



OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(PATH_SRC),$(SRC))
OBJS = $(addprefix $(PATH_OBJ),$(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(PATH_LIB)
	@gcc $(CFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@
	@echo "$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_LEXER) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_TOOLS) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_PARSER) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_PROMPT) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_BUILT) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_ERROR) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_TERMCAPS) 2> /dev/null || true
	@gcc $(CFLAGS) -I $(INCLUDE) -o $@ -c $<
	@echo " "
	@printf "\033[1A"
	@./progress_bar.sh $(NAME) $(shell ls -lR $(PATH_SRC) 2> /dev/null | grep -c -o "\.c") $(shell ls -lR $(PATH_OBJ) 2> /dev/null | grep -c -o "\.o")
	@#./progress_bar.sh $(NAME) 11 $(shell ls -lR $(PATH_OBJ) 2> /dev/null | grep -c -o "\.o")

clean:
	@/bin/rm -f $(OBJS)
	@make clean -C $(PATH_LIB)
	@rmdir $(PATH_OBJ)$(PATH_LEXER) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_TOOLS) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_PARSER) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_BUILT) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_PROMPT) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_ERROR) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_TERMCAPS) 2> /dev/null || true
	@rmdir $(PATH_OBJ) 2> /dev/null || true

fclean: clean
	@make fclean -C $(PATH_LIB)
	@rm -f $(NAME)
	@echo "$(NAME):\t\t\t$(GREEN)[CLEAN]$(END)"

re: fclean all

norme:
	norminette $(SRC)
	norminette ./includes/

debug: $(OBJS)
	@make -C $(PATH_LIB)
	gcc $(CFLAGS) $(LDFLAGS) $(LDLIBS ) -fsanitize=address -g3 $^ -o $(NAME)
