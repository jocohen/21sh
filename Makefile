# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcollard <tcollard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/26 16:54:18 by tcollard          #+#    #+#              #
#    Updated: 2018/12/12 16:59:10 by tcollard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, debug, norme

NAME = 21sh

END = \x1b[0m
GREEN = \x1b[32m

CFLAGS = -Wall -Werror -Wextra
LDFLAGS = -Llibft
LDLIBS = -lft

PATH_LEXER = lexer/
PATH_PROMPT = prompt/
PATH_TOOLS = tools/
PATH_PARSER = parser/
PATH_BUILT = builtins/
PATH_OPERATOR = operator/
PATH_ERROR = error/

INCLUDE = ./includes/
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
		$(PATH_BUILT)echo.c \
		$(PATH_BUILT)cd.c \
		$(PATH_BUILT)setenv.c \
		$(PATH_BUILT)unsetenv.c \
		$(PATH_BUILT)env.c \
		$(PATH_BUILT)exec_input.c \
		$(PATH_TOOLS)lexer_tools.c \
		$(PATH_TOOLS)clean_tools.c \
		$(PATH_TOOLS)split_tools.c \
		$(PATH_TOOLS)split_tools_2.c \
		$(PATH_TOOLS)quote_tools.c \
		$(PATH_TOOLS)parser_tools.c \
		$(PATH_TOOLS)env_tools.c \
		$(PATH_TOOLS)env_tools_2.c \
		$(PATH_OPERATOR)pipe.c \
		$(PATH_OPERATOR)job_control.c \
		$(PATH_PROMPT)minishell.c \
		$(PATH_PROMPT)quote_prompt.c \
		$(PATH_ERROR)lexer_error.c \
		$(PATH_ERROR)parser_error.c \
		$(PATH_ERROR)error_cd.c \
		$(PATH_ERROR)exec_error.c \
		$(PATH_ERROR)error_setenv.c \
		$(PATH_ERROR)error_unsetenv.c

OBJ = $(SRC:.c=.o)

SRCS = $(addprefix $(PATH_SRC),$(SRC))
OBJS = $(addprefix $(PATH_OBJ),$(OBJ))

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(PATH_LIB)
	@gcc $(CFLAGS) -g3 -o $@ $(OBJS) ./libft/libft.a
	@echo "\n$(NAME):\t\t\t$(GREEN)[READY]\n\t\t¯\_(ツ)_/¯$(END)"

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_LEXER) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_TOOLS) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_PARSER) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_PROMPT) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_BUILT) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_ERROR) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_OPERATOR) 2> /dev/null || true
	@gcc $(CFLAGS) -g3 -I $(INCLUDE) -o $@ -c $<
	@echo " "
	@printf "\033[1A"
	@./progress_bar.sh $(NAME) $(shell ls -lR $(PATH_SRC) 2> /dev/null | grep -c -o "\.c") $(shell ls -lR $(PATH_OBJ) 2> /dev/null | grep -c -o "\.o")

clean:
	@/bin/rm -f $(OBJS)
	@make clean -C $(PATH_LIB)
	@rmdir $(PATH_OBJ)$(PATH_LEXER) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_TOOLS) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_PARSER) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_BUILT) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_PROMPT) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_ERROR) 2> /dev/null || true
	@rmdir $(PATH_OBJ)$(PATH_OPERATOR) 2> /dev/null || true
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
	@gcc $(CFLAGS) -fsanitize=address -g3 -o $(NAME) $(OBJS) ./libft/libft.a
