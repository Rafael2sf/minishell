# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 10:54:37 by rafernan          #+#    #+#              #
#    Updated: 2022/04/07 10:58:44 by rafernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################# PROGRAM ###############

NAME	=		minishell

################### TERMINAL ############

RMV		=		rm -f
MKD		=		mkdir
PRT		=		printf
MKE		=		make
CPY		=		cp
NRM		=		norminette

################### COLORS ##############

--GRN	=		\033[32m
--RED	=		\033[31m
--WHT	=		\033[39m

################### DIRS ################

_SRC	=		src/
_OBJ	=
_LIB	=

################### COMPILER ############

CC		=		gcc
AR		=		ar rcs
CFLAGS	=		-O2
DBFLAGS	=		-g -Wall -Werror -Wextra -D DEBUG=1

################### FILES ###############

SRCS_	=		minishell.c \
				\
				builtins/cd/ft_cd.c \
				builtins/echo/ft_echo.c \
				builtins/env/ft_env.c \
				builtins/exit/ft_exit.c \
				builtins/export/create_export.c \
				builtins/export/ft_export.c \
				builtins/export/ft_realloc.c \
				builtins/export/new_var_output_prep.c \
				builtins/export/parse_name_export.c \
				builtins/pwd/ft_pwd.c \
				builtins/unset/ft_realloc_unset.c \
				builtins/unset/ft_unset.c \
				builtins/unset/parse_name_unset.c \
				\
				executor/ast_execute.c \
				executor/hdoc.c \
				executor/input.c \
				executor/output.c \
				executor/search.c \
				\
				parse/ast_add.c \
				parse/ast_add_type.c \
				parse/ast_utils.c \
				parse/create_token.c \
				parse/matrix_utils.c \
				parse/parse.c \
				parse/parse_exp.c \
				parse/parse_token.c \
				\
				parse/parse_utils.c \
				utils/altered_split.c \
				utils/change_shlvl.c \
				utils/env_cpy.c \
				utils/env_start_prep.c \
				utils/ptr_ptr_free.c \
				utils/tk_print.c

SRCS	=		$(addprefix $(_SRC), $(SRCS_))
OBJS	=		$(patsubst %.c, %.o,$(SRCS))

DEPS	=		libft/libft.a
LIBS	=		-lft -lreadline

################### RULES ###############

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
#	@$(NRM)	$<

debug:
	$(MAKE) $(NAME) CFLAGS="$(DBFLAGS)"

$(NAME): $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME) -L./libft

libft/libft.a: $(shell make -C libft/ -q libft.a || echo force)
	$(MKE) libft.a -C libft/

################### STRUCTURE ###########

$(_OBJ):
	$(MKD) $@

$(_LIB):
	$(MKD) $@

$(_SRC):
	$(MKD) $@

################### CLEAN ###############

clean:
	$(MKE) clean -C libft/
	$(RMV) $(OBJS)

fclean: clean
	$(MKE) fclean -C libft/
	$(RMV) $(_LIB)$(NAME)

re: fclean all

.PHONY: all debug clean fclean re force