# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrlouf                                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#              #
#    Updated: 2026/02/10 13:57:00 by mrlouf           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= nm

# Directories
SRC_DIR		= src
INC_DIR		= inc
LIBFT_DIR	= libft

# Source files
SRCS		= $(SRC_DIR)/main.c

# Object files
OBJS		= $(SRCS:.c=.o)

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft

# Colors for pretty output
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RESET		= \033[0m

# Main target
all: $(NAME)

# Build the nm binary
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

# Compile object files
%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build libft
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compiled successfully!$(RESET)"

# Clean object files
clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@/bin/rm -f $(OBJS)
	@echo "$(GREEN)Clean complete!$(RESET)"

# Clean everything
fclean: clean
	@echo "$(YELLOW)Removing binaries...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)Full clean complete!$(RESET)"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re
