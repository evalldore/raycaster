#include "raycaster.h"

SDL_Window		*g_window = NULL;
SDL_GLContext	g_context;
GLuint			g_vertexArrayObject = 0;
GLuint			g_vertexBufferObject = 0;
GLuint			g_vertexBufferObject2 = 0;
GLuint			g_graphicsPipelineShader = 0;

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
		Game_Update(delta_time);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);
		glViewport(0, 0, WIDTH, HEIGHT);
		glClearColor(1.0f, 0.5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(g_graphicsPipelineShader);
		//Draw
		glBindVertexArray(g_vertexArrayObject);
		glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(0);
		//Game_Draw();
		SDL_GL_SwapWindow(g_window);
		last_ticks = current_ticks;
	}
}

static void		Init()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		printf("SDL Failed to initalize!");
		exit(EXIT_FAILURE);
	}
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	g_window = SDL_CreateWindow("Raycaster", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (!g_window)
	{
		printf("SDL failed to create window!");
		exit(EXIT_FAILURE);
	}
	g_context = SDL_GL_CreateContext(g_window);
	if (!g_context)
	{
		printf("SDL failed to create OpenGL Context!");
		exit(EXIT_FAILURE);
	}
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		printf("GLAD failed to initalize!");
		exit(EXIT_FAILURE);
	}
	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("Shading language version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	Game_Init();
}

static void		Exit()
{
	printf("exiting\n");
	Game_Exit();
	SDL_GL_DeleteContext(g_context);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}

void	VertexSpecification()
{
	// cpu vertices
	const GLfloat vertexPosition[3][3] = {
		{-0.8f, -0.8f, 0.0f},
		{0.8f, -0.8f, 0.0f},
		{0.0f, 0.8f, 0.0f}
	};

	const GLfloat vertexColors[3][3] = {
		{1.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 1.0f}
	};
	//gpu setup
	glGenVertexArrays(1, &g_vertexArrayObject);
	glBindVertexArray(g_vertexArrayObject);

	//start generating VBO
	//position
	glGenBuffers(1, &g_vertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPosition), &vertexPosition, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	//colors
	glGenBuffers(1, &g_vertexBufferObject2);
	glBindBuffer(GL_ARRAY_BUFFER, g_vertexBufferObject2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexColors), &vertexColors, GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindVertexArray(0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

}

GLuint	CompileShader(GLuint type, const char *src)
{
	GLuint	shaderObject;
	GLint	result;
	GLint	len;

	if (type == GL_VERTEX_SHADER)
	{
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (type == GL_FRAGMENT_SHADER)
	{
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	}
	glShaderSource(shaderObject, 1, &src, NULL);
	glCompileShader(shaderObject);

	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &len);
		GLchar	errorMessages[len];
		glGetShaderInfoLog(shaderObject, len, &len, errorMessages);

		if (type == GL_VERTEX_SHADER)
			printf("ERROR: GL_VERTEX_SHADER\n");
		else if (type == GL_FRAGMENT_SHADER)
			printf("ERROR: GL_FRAGMENT_SHADER\n");
		printf("%s\n", errorMessages);
		glDeleteShader(shaderObject);
		return (0);
	}
	return (shaderObject);
}

GLuint	CreateShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
	GLuint	programObject = glCreateProgram();
	GLuint	vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	glLinkProgram(programObject);

	//Valid program
	glValidateProgram(programObject);

	return (programObject);
}

char	*LoadShader(const char	*filename)
{
	char	*results;
	char	*line;
	char	*temp;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	results = malloc(sizeof(char));
	results[0] = '\0';
	while((line = ft_get_next_line(fd)))
	{
		temp = results;
		results = ft_strjoin(results, line);
		free(temp);
		free(line);
	}
	close(fd);
	return (results);
}

void	CreateGraphicsPipeline()
{
	char	*vertexShaderSrc;
	char	*fragmentShaderSrc;

	vertexShaderSrc = LoadShader("./shaders/test_vert.glsl");
	fragmentShaderSrc = LoadShader("./shaders/test_frag.glsl");
	g_graphicsPipelineShader = CreateShaderProgram(vertexShaderSrc, fragmentShaderSrc);
	free(vertexShaderSrc);
	free(fragmentShaderSrc);
}

int	main(int argc, char *argv)
{
	Init();
	VertexSpecification();
	CreateGraphicsPipeline();
	Loop();
	Exit();
	return (EXIT_SUCCESS);
}