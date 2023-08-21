NAME		= raycaster
SRCS		= main.c assets.c game.c map.c renderer.c utils.c entities.c sprites.c camera.c \
				components/position.c components/sprite.c
BINDIR		= bin/
SRCDIR		= src/
INCLUDE		= -I include/ -I glad/include -I $(LIBFT)/include -I $(ECS)/include
OBJS		= $(addprefix $(BINDIR), $(SRCS:.c=.o))
RM			= rm -r
SDL2		= `sdl2-config --cflags --libs`
CFLAGS		= -ldl
LIBFT		= ./lib/libft
ECS			= ./lib/ecs
CC			= gcc
LIBS		= $(ECS)/ecs.a $(LIBFT)/libft.a -lm

all : ecs libft $(NAME)

libft:
	$(MAKE) -C $(LIBFT)

ecs:
	$(MAKE) -C $(ECS)

$(NAME) : $(BINDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $@ glad/src/glad.c $(OBJS) $(LIBS) `sdl2-config --libs` $(INCLUDE)

$(BINDIR)%.o : $(SRCDIR)%.c 
	$(CC) $(CFLAGS) -c -o $@ $< `sdl2-config --cflags` $(INCLUDE)

$(BINDIR) :
	mkdir $(BINDIR)
	mkdir $(BINDIR)/components

clean :
	$(RM) -d $(BINDIR)
	$(MAKE) -C $(LIBFT) fclean
	$(MAKE) -C $(ECS) fclean

fclean : clean
	$(RM) $(NAME)

re : fclean all
