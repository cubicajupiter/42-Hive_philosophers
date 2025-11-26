# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jvalkama <jvalkama@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/18 12:06:00 by jvalkama          #+#    #+#              #
#    Updated: 2025/11/20 17:13:17 by jvalkama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:=philo

SRCDIR			:=srcs
VPATH			:=$(SRCDIR)
SRCS			:=main.c inits.c parser.c run_sim.c routines.c waiter.c mutex.c

OBJDIR			:=objs
OBJS			:=$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

COMPILER		:=cc
CFLAGS			:=-Wall -Wextra -Werror -g -pthread #-O3 -march=native

INC_DIR			:=includes
INCLUDES		:=-I $(INC_DIR)

HEADER			:=$(INC_DIR)/philosophers.h

RM				:=rm -f


all:				$(NAME)

$(OBJDIR):
						mkdir -p $(OBJDIR)

$(NAME):			$(OBJS)
						@echo "linking $@"
						$(COMPILER) $(CFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o:		$(SRCDIR)/%.c $(HEADER) | $(OBJDIR)
						@echo "Compiling $<"
						$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
						@echo "Cleaning object files"
						@$(RM) $(OBJS)

fclean:				clean
						@echo "Cleaning all"
						@$(RM) $(NAME)
						@$(RM) -rf $(OBJDIR)

re:					fclean all

.PHONY: all clean fclean re
