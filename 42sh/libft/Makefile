# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jocohen <jocohen@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 17:14:32 by jocohen           #+#    #+#              #
#    Updated: 2018/10/01 19:41:35 by jocohen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re

NAME = libft.a

CFLAGS = -Wall -Werror -Wextra

INCLUDE =
PATH_PRINTF = printf/
PATH_SRC = ./
PATH_OBJ = ./obj/

NAME_SRC = ft_atoi.c \
		   ft_bzero.c \
		   ft_isalnum.c \
		   ft_isalpha.c \
		   ft_isascii.c \
		   ft_isdigit.c \
		   ft_isprint.c \
		   ft_itoa.c \
		   ft_lstadd.c \
		   ft_lstdel.c \
		   ft_lstdelone.c \
		   ft_lstiter.c \
		   ft_lstmap.c \
		   ft_lstnew.c \
		   ft_lstsize.c \
		   ft_memalloc.c \
		   ft_memccpy.c \
		   ft_memchr.c \
		   ft_memcmp.c \
		   ft_memcpy.c \
		   ft_memdel.c \
		   ft_memmove.c \
		   ft_memset.c \
		   ft_putchar.c \
		   ft_putchar_fd.c \
		   ft_putendl.c \
		   ft_putendl_fd.c \
		   ft_putnbr.c \
		   ft_putnbr_fd.c \
		   ft_putstr.c \
		   ft_putstr_fd.c \
		   ft_strcat.c \
		   ft_strcatc.c \
		   ft_strchr.c \
		   ft_strclr.c \
		   ft_strcmp.c \
		   ft_strcpy.c \
		   ft_strdel.c \
		   ft_strdup.c \
		   ft_strequ.c \
		   ft_striter.c \
		   ft_striteri.c \
		   ft_strjoin.c \
		   ft_strlcat.c \
		   ft_strlen.c \
		   ft_strmap.c \
		   ft_strmapi.c \
		   ft_strncat.c \
		   ft_strncmp.c \
		   ft_strncpy.c \
		   ft_strnequ.c \
		   ft_strnew.c \
		   ft_strnstr.c \
		   ft_strrchr.c \
		   ft_strsplit.c \
		   ft_strstr.c \
		   ft_strsub.c \
		   ft_strtrim.c \
		   ft_strwhcpy.c \
		   ft_tolower.c \
		   ft_toupper.c \
		   ft_strwhlen.c \
		   ft_lstfind.c \
		   ft_memdel2.c \
		   ft_itoa_base.c \
		   ft_strrev.c \
		   ft_atoi_base.c \
		   ft_putwstr.c \
		   ft_wstrlen.c \
		   ft_unicode.c \
		   ft_lenbyte.c \
		   ft_memdel_0.c \
		   ft_path.c \
		   ft_twod_dup.c \
		   $(PATH_PRINTF)captain.c \
		   $(PATH_PRINTF)captain_2.c \
		   $(PATH_PRINTF)character.c \
		   $(PATH_PRINTF)check_flags.c \
		   $(PATH_PRINTF)count_flags.c \
		   $(PATH_PRINTF)deci.c \
		   $(PATH_PRINTF)fill_flags.c \
		   $(PATH_PRINTF)ft_itoa_base_ulonglong.c \
		   $(PATH_PRINTF)ft_itoa_longlong.c \
		   $(PATH_PRINTF)ft_itoa_ulonglong.c \
		   $(PATH_PRINTF)ft_mult_del.c \
		   $(PATH_PRINTF)ft_prefixstr.c \
		   $(PATH_PRINTF)ft_printf.c \
		   $(PATH_PRINTF)get_flags.c \
		   $(PATH_PRINTF)hexa.c \
		   $(PATH_PRINTF)int.c \
		   $(PATH_PRINTF)octal.c \
		   $(PATH_PRINTF)print_local.c \
		   $(PATH_PRINTF)sailor.c \
		   $(PATH_PRINTF)string.c \
		   $(PATH_PRINTF)until_percent.c \
		   $(PATH_PRINTF)w_precision.c \
		   $(PATH_PRINTF)wchar.c \
		   $(PATH_PRINTF)wstring.c \
		   get_next_line.c \
		   ft_ldbl_funcs.c

NAME_OBJ = $(SRC:.c=.o)

SRC = $(addprefix $(PATH_SRC),$(NAME_SRC))
OBJ = $(addprefix $(PATH_OBJ),$(NAME_OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $@ $^
	@ranlib $@

$(PATH_OBJ)%.o : $(PATH_SRC)%.c
	@mkdir $(PATH_OBJ) 2> /dev/null || true
	@mkdir $(PATH_OBJ)$(PATH_PRINTF) 2> /dev/null || true
	@gcc $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@rmdir $(PATH_OBJ)$(PATH_PRINTF) 2> /dev/null || true
	@rmdir $(PATH_OBJ) 2> /dev/null || true

fclean: clean
	@rm -f $(NAME)

re: fclean all
