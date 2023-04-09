SRCS		= main.c components.c
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
NAME		= ecs.a
INCDIR		= include/
BINDIR		= bin/
SRCDIR		= src/
LIBC		= ar rcs
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
CC			= gcc

all : $(NAME)

$(BINDIR)%.o : $(SRCDIR)%.c
	$(CC) -c $(CFLAGS) -o $@ $^ -I $(INCDIR)

$(NAME) : $(BINDIR) $(OBJS)
	$(LIBC) $@ $(OBJS)

$(BINDIR) :
	mkdir $(BINDIR)

clean :
	$(RM) -r $(BINDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all