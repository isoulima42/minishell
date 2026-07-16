# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/16 09:22:39 by isoulima          #+#    #+#              #
#    Updated: 2026/08/27 10:02:34 by isoulima         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC		= cc
CFLAGS		= -Wall -Wextra -Werror

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
LIBS		= -L$(LIBFT_DIR) -lft -lreadline

SRCS		= src/main.c \
		  src/loop.c \
		  src/env/env_init.c \
		  src/env/env_utils.c \
		  src/env/env_set.c \
		  src/env/env_free.c \
		  src/lexer/lexer.c \
		  src/lexer/lexer_word.c \
		  src/lexer/lexer_utils.c \
		  src/parser/parser.c \
		  src/parser/parser_redir.c \
		  src/parser/parser_utils.c \
		  src/parser/syntax.c \
		  src/expand/expand.c \
		  src/expand/expand_word.c \
		  src/expand/expand_var.c \
		  src/expand/expand_build.c \
		  src/expand/expand_finish.c \
		  src/exec/execute.c \
		  src/exec/pipeline.c \
		  src/exec/exec_child.c \
		  src/exec/redir.c \
		  src/exec/path.c \
		  src/exec/exec_utils.c \
		  src/heredoc/heredoc.c \
		  src/builtins/builtin_dispatch.c \
		  src/builtins/builtin_echo.c \
		  src/builtins/builtin_pwd_env.c \
		  src/builtins/builtin_cd.c \
		  src/builtins/builtin_export.c \
		  src/builtins/builtin_export_utils.c \
		  src/builtins/builtin_unset.c \
		  src/builtins/builtin_exit.c \
		  src/signals/signals.c \
		  src/utils/error.c \
		  src/utils/free_utils.c \
		  src/utils/str_utils.c

OBJS		= $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)

%.o: %.c include/minishell.h
	$(CC) $(CFLAGS) -I include -I $(LIBFT_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
