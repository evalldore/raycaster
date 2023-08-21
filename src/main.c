#include "raycaster.h"

SDL_Window		*g_window = NULL;

static void	Loop()
{
	SDL_Event	event;
	bool		running;
	uint32_t	current_ticks;
	uint32_t	last_ticks;
	double		delta_time;

	running = true;
	last_ticks = 0;
	while(running)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
					return ;
				case SDL_KEYDOWN:
					Game_KeyPressed(event.key);
					break;
				case SDL_KEYUP:
					Game_KeyReleased(event.key);
					break;
				default:
					break;
			}
		}
		current_ticks = SDL_GetTicks();
		delta_time = (double)(current_ticks - last_ticks) / 1000.0;
		//char *fpsText = ft_itoa((int)(1000.f / delta_time));
		//SDL_SetWindowTitle(g_window, fpsText);
		Game_Update(delta_time);
		Renderer_PreDraw();
		Game_Draw();
		Renderer_PostDraw();
		SDL_GL_SwapWindow(g_window);
		last_ticks = current_ticks;
	}
}

static void		Init()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "SDL Failed to initalize!");
		exit(EXIT_FAILURE);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	g_window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	//SDL_SetWindowFullscreen(g_window, SDL_WINDOW_FULLSCREEN);
	if (!g_window)
	{
		fprintf(stderr, "SDL failed to create window!");
		exit(EXIT_FAILURE);
	}
	Renderer_Init(g_window);
	float piss[2];
	Game_Init();
}

static void		Exit()
{
	printf("exiting\n");
	Game_Exit();
	Renderer_Clear();
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

int	main(void)
{
	Init();
	Loop();
	Exit();
	return (EXIT_SUCCESS);
}