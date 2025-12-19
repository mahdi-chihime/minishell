# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mchihime <mchihime@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 20:20:41 by rakhaled          #+#    #+#              #
#    Updated: 2025/12/19 15:14:21 by mchihime         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET	= \033[0m
GREEN	= \033[32m
BLUE	= \033[34m
YELLOW	= \033[33m
RED		= \033[31m
BOLD	= \033[1m

define PRINT_BANNER
	@printf "%b\n" "$(BLUE)" \
" __  __ _       _     _          _ _" \
"|  \\/  (_)_ __ (_)___| |__   ___| | |" \
"| |\\/| | | '_ \\| / __| '_ \\ / _ \\ | |" \
"| |  | | | | | | \\__ \\ | | |  __/ | |" \
"|_|  |_|_|_| |_|_|___/_| |_|\\___|_|_|" \
"$(RESET)"
endef

NAME	= minishell

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I.

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC = builtin_cd.c builtin_exit.c env_convert.c env_from.c env_ops.c \
	error_utils.c exec_builtin.c exec_builtin2.c exec_builtin3.c exec_builtin_dispatch.c \
	exec_builtin_runner.c exec_fd.c exec_main.c exec_main_utils.c exec_path.c \
	exec_pipes.c exec_redir.c exec_subshell.c expand_wildcards.c \
	export_utils.c free_utils.c heredoc.c heredoc2.c home_utils.c input_utils.c \
	lexer.c lexer_add_token.c lexer_expand_quotes.c lexer_expand_utils.c \
	lexer_expand_word.c lexer_handle.c lexer_operators.c lexer_utils.c main.c \
	parse_args.c parser.c parser_append_args.c parser_ast.c parser_command.c \
	parser_pipeline.c parser_redir.c parser_subshell.c signal.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(PRINT_BANNER)
	@echo "$(YELLOW)Stirring sources...$(RESET)"
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)WaW SO NICE -> $(NAME) ready$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)Compiled$(RESET) $< $(BOLD)✓$(RESET)"

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
