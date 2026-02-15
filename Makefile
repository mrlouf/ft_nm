# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicolas <nicolas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/10 13:57:00 by mrlouf            #+#    #+#              #
#    Updated: 2026/02/15 13:36:08 by nicolas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_nm

SRC_DIR		= src
INC_DIR		= inc
LIBFT_DIR	= libft

SRC			= main.c		\
			parse.c			\
			process.c		\
			utils.c			\
			sort.c

SRCDIR		= src
SRCS		= $(addprefix $(SRCDIR)/, $(SRC))

OBJDIR		= .obj
OBJS		= $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

DEPDIR		= .dep
DEPS		= $(addprefix $(DEPDIR)/, $(SRC:.c=.d))
DEPDIRS		= $(DEPDIR)

LIBFT		= $(LIBFT_DIR)/libft.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g# -fsanitize=address
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft
DFLAGS		= -MT $@ -MMD -MP

GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RESET		= \033[0m

MAKE		= make

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS) Makefile
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -MT $@ -MMD -MP -c $< -o $@
	@mkdir -p $(DEPDIR)
	@mv $(patsubst %.o,%.d,$@) $(subst $(OBJDIR),$(DEPDIR),$(@D))/

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)libft compiled successfully!$(RESET)"

clean:
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean
	@/bin/rm -f $(OBJS)
	@echo "$(GREEN)Clean complete!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing binaries...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@/bin/rm -f $(NAME)
	@echo "$(GREEN)Full clean complete!$(RESET)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
