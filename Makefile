NAME		= raycaster
SRCS		= main.c game.c vector.c
BINDIR		= bin/
SRCDIR		= src/
INCLUDE		= -I include/ -I glad/include
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
RM			= rm -r
SDL2		= `sdl2-config --cflags --libs`
CFLAGS		= -ldl
CC			= gcc

all : $(NAME)

$(NAME) : $(BINDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ glad/src/glad.c $(OBJS) `sdl2-config --libs` $(INCLUDE)

$(BINDIR)%.o : $(SRCDIR)%.c 
	$(CC) $(CFLAGS) -c -o $@ $< `sdl2-config --cflags` $(INCLUDE)

$(BINDIR) :
	mkdir $(BINDIR)

clean :
	$(RM) -d $(BINDIR)

fclean : clean
	$(RM) $(NAME)

re : fclean all
