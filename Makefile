# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qdeffaux <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/22 12:43:58 by qdeffaux          #+#    #+#              #
#    Updated: 2025/09/22 12:44:01 by qdeffaux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		= philo

# Compiler and flags
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# Source files listed individually
SRCS		= main.c \
			  utils.c \
			  init_philo.c \
			  init_helper.c \
			  setup_philo.c \
			  action_philo.c \
			  action_philo2.c \
			  monitor.c \
			  cleanup.c

# Object files
OBJS		= $(SRCS:.c=.o)

# Header file
HEADER		= philo.h

# Colors
GREEN		= \033[0;32m
RED			= \033[0;31m
YELLOW		= \033[0;33m
RESET		= \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

main.o: main.c $(HEADER)
	@echo "$(YELLOW)Compiling main.c...$(RESET)"
	@$(CC) $(CFLAGS) -c main.c -o main.o

utils.o: utils.c $(HEADER)
	@echo "$(YELLOW)Compiling utils.c...$(RESET)"
	@$(CC) $(CFLAGS) -c utils.c -o utils.o

init_philo.o: init_philo.c $(HEADER)
	@echo "$(YELLOW)Compiling init_philo.c...$(RESET)"
	@$(CC) $(CFLAGS) -c init_philo.c -o init_philo.o

init_helper.o: init_helper.c $(HEADER)
	@echo "$(YELLOW)Compiling init_helper.c...$(RESET)"
	@$(CC) $(CFLAGS) -c init_helper.c -o init_helper.o

setup_philo.o: setup_philo.c $(HEADER)
	@echo "$(YELLOW)Compiling setup_philo.c...$(RESET)"
	@$(CC) $(CFLAGS) -c setup_philo.c -o setup_philo.o

action_philo.o: action_philo.c $(HEADER)
	@echo "$(YELLOW)Compiling action_philo.c...$(RESET)"
	@$(CC) $(CFLAGS) -c action_philo.c -o action_philo.o

action_philo2.o: action_philo2.c $(HEADER)
	@echo "$(YELLOW)Compiling action_philo2.c...$(RESET)"
	@$(CC) $(CFLAGS) -c action_philo2.c -o action_philo2.o

monitor.o: monitor.c $(HEADER)
	@echo "$(YELLOW)Compiling monitor.c...$(RESET)"
	@$(CC) $(CFLAGS) -c monitor.c -o monitor.o

cleanup.o: cleanup.c $(HEADER)
	@echo "$(YELLOW)Compiling cleanup.c...$(RESET)"
	@$(CC) $(CFLAGS) -c cleanup.c -o cleanup.o

clean:
	@rm -f $(OBJS)
	@echo "$(RED)✓ Object files removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)✓ $(NAME) removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
