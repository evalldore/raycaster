NAME		= raycaster
SRCS		= main.c game.c map.c renderer.c utils.c
BINDIR		= bin/
SRCDIR		= src/
INCLUDE		= -I include/ -I glad/include -I $(LIBFT)/include
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
RM			= rm -r
SDL2		= `sdl2-config --cflags --libs`
CFLAGS		= -ldl
LIBFT		= ./lib/libft
CC			= gcc
LIBS		= $(LIBFT)/libft.a -lm

all : libft $(NAME)

libft:
	$(MAKE) -C $(LIBFT)

$(NAME) : $(BINDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ glad/src/glad.c $(OBJS) $(LIBS) `sdl2-config --libs` $(INCLUDE)

$(BINDIR)%.o : $(SRCDIR)%.c 
	$(CC) $(CFLAGS) -c -o $@ $< `sdl2-config --cflags` $(INCLUDE)

$(BINDIR) :
	mkdir $(BINDIR)

clean :
	$(RM) -d $(BINDIR)
	$(MAKE) -C $(LIBFT) fclean

fclean : clean
	$(RM) $(NAME)

re : fclean all
