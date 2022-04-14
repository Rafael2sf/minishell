# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafernan <rafernan@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 10:54:37 by rafernan          #+#    #+#              #
#    Updated: 2022/04/14 13:10:55 by rafernan         ###   ########.fr        #
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

CC		=		cc
AR		=		ar rcs
CFLAGS	=		-Wall -Werror -Wextra -O2
DBFLAGS	=		-g -Wall -Werror -Wextra -D DEBUG=1

################### FILES ###############

SRCS_	=		\
				main/main.c \
				main/envp.c \
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
				executor/executor.c \
				\
				lexer/ast_add.c \
				lexer/ast.c \
				lexer/ast_utils.c \
				lexer/lexer.c \
				lexer/lexer_to_ast.c \
				lexer/lexer_token.c \
				lexer/lexer_utils.c \
				\
				parser/builtin.c \
				parser/expand.c \
				parser/hdoc.c \
				parser/input.c \
				parser/output.c \
				parser/parser.c \
				parser/parser_utils.c \
				parser/search.c \
				\
				utils/ast_iter.c \
				utils/ast_print.c \
				utils/ms_split.c \
				utils/pp_utils.c \
				utils/signal_handling.c \
				utils/ms_exit.c

SRCS	=		$(addprefix $(_SRC), $(SRCS_))
OBJS	=		$(patsubst %.c, %.o,$(SRCS))

DEPS	=		libft/libft.a
LIBS	=		-lft -lreadline

INCS	=		-I  ~/.brew/opt/readline/include -I ./headers/
LKNS	=		-L ./libft -L ~/.brew/opt/readline/lib -L /usr/lib/x86_64-linux-gnu/

################### RULES ###############

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
#	$(NRM) $<

debug:
	$(MAKE) $(NAME) CFLAGS="$(DBFLAGS)"

$(NAME): $(DEPS) $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME) $(INCS) $(LKNS) $(DEPS)

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
 