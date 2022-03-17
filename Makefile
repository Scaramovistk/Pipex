# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gscarama <gscarama@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 12:08:26 by gscarama          #+#    #+#              #
#    Updated: 2022/03/17 13:12:44 by gscarama         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

SOURCE	= main.c \
			pipex.c \
			ft_split.c \
			utils.c

GCC		= gcc
RM		= rm -rf
CFLAGS	= -Wall -Wextra -Werror -g
HEADER	= incl
PATH_SRC	= srcs
PATH_OBJ	= objs

SRCS	= $(addprefix $(PATH_SRC)/,$(SOURCE))
OBJS	= $(addprefix $(PATH_OBJ)/,$(SOURCE:.c=.o))

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.c
			${GCC} ${CFLAGS} -c $< -o ${<:$(PATH_SRC)/%.c=$(PATH_OBJ)/%.o}

${NAME}:	${OBJS}
			$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re .c.o
