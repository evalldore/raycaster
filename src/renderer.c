#include "renderer.h"

SDL_GLContext	g_context;
GLuint			g_graphicsPipelineShader = 0;
GLuint			g_imageShader = 0;
GLfloat			g_shaderColor[3] = {1.0f, 1.0f, 1.0f};
GLuint			g_imageVertexArray = 0;
GLuint			g_imageVertexBuffer = 0;
GLuint			g_imageIndexBuffer = 0;
GLuint			g_lineVertexArray = 0;
GLuint			g_lineVertexBuffer = 0;
GLuint			g_pointVertexArray = 0;
GLuint			g_pointVertexBuffer = 0;
GLuint			g_rectVertexArray = 0;
GLuint			g_rectVertexBuffer = 0;
GLuint			g_rectIndexBuffer = 0;

const char* GLErrorString(GLenum error)
{
    switch (error)
    {
        case GL_NO_ERROR:          return "No error";
        case GL_INVALID_ENUM:      return "Invalid enum";
        case GL_INVALID_VALUE:     return "Invalid value";
        case GL_INVALID_OPERATION: return "Invalid operation";
        case GL_STACK_OVERFLOW:    return "Stack overflow";
        case GL_STACK_UNDERFLOW:   return "Stack underflow";
        case GL_OUT_OF_MEMORY:     return "Out of memory";
        default:                   return "Unknown error";
    }
}

void		GLClearAllErrors()
{
	while(glGetError() != GL_NO_ERROR) {}
}

bool		GLCheckErrorStatus(const char *function, int line)
{
	GLenum	error;

	while((error = glGetError()))
	{
		fprintf(stderr, "OpenGL error: %s\n\tLine: %d\n\tFunction: %s\n", GLErrorString(error), line, function);
		return (true);
	}
	return (false);
}

static char* readFileToBuffer(const char* filename) {
	FILE *file = fopen(filename, "rb");
	if (!file) {
		perror("Failed to open file");
		return NULL;
	}

	// Seek to the end of the file to determine its size
	fseek(file, 0, SEEK_END);
	long filesize = ftell(file);
	fseek(file, 0, SEEK_SET); // Reset to the beginning of the file

	// Allocate buffer to hold the file content + 1 byte for the null terminator
	char *buffer = malloc(filesize + 1);
	if (!buffer) {
		perror("Failed to allocate memory");
		fclose(file);
		return NULL;
	}

	// Read the entire file into the buffer
	size_t bytesRead = fread(buffer, 1, filesize, file);
	if (bytesRead != filesize) {
		perror("Failed to read the entire file");
		free(buffer);
		fclose(file);
		return NULL;
	}

	// Set the last byte of the buffer to 0
	buffer[filesize] = 0;

	fclose(file);
	return buffer;
}

static char	*LoadShader(const char	*filename)
{
	return (readFileToBuffer(filename));
}

static GLuint	CompileShader(GLuint type, const char *src)
{
	GLuint	shaderObject;
	GLint	result;
	GLint	len;

	if (type == GL_VERTEX_SHADER)
		shaderObject = glCreateShader(GL_VERTEX_SHADER);
	else if (type == GL_FRAGMENT_SHADER)
		shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shaderObject, 1, &src, NULL);
	glCompileShader(shaderObject);
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &len);
		GLchar	errorMessages[len];
		glGetShaderInfoLog(shaderObject, len, &len, errorMessages);
		if (type == GL_VERTEX_SHADER)
			fprintf(stderr, "ERROR: GL_VERTEX_SHADER\n");
		else if (type == GL_FRAGMENT_SHADER)
			fprintf(stderr, "ERROR: GL_FRAGMENT_SHADER\n");
		fprintf(stderr, "%s\n", errorMessages);
		glDeleteShader(shaderObject);
		return (0);
	}
	return (shaderObject);
}

static GLuint	CreateShaderProgram(const char *vertexShaderSource, const char *fragmentShaderSource)
{
	GLuint	programObject = glCreateProgram();
	GLuint	vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	GLuint	fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);
	glLinkProgram(programObject);

	//Valid program
	glValidateProgram(programObject);

	int success;
	char infoLog[512];
	glGetProgramiv(programObject, GL_VALIDATE_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programObject, 512, NULL, infoLog);
		fprintf(stderr, "Program validation failed:\n%s\n", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return (programObject);
}

void Renderer_SetColor(float r, float g, float b)
{
	g_shaderColor[0] = r;
	g_shaderColor[1] = g;
	g_shaderColor[2] = b;
}

GLuint	Renderer_CreateShader(const char *vertPath, const char *fragPath)
{
	char	*vertexShaderSrc;
	char	*fragmentShaderSrc;
	GLuint	shaderProgram = 0;

	vertexShaderSrc = LoadShader(vertPath);
	fragmentShaderSrc = LoadShader(fragPath);
	if (vertexShaderSrc && fragmentShaderSrc)
	{
		shaderProgram = CreateShaderProgram(vertexShaderSrc, fragmentShaderSrc);
		free(vertexShaderSrc);
		free(fragmentShaderSrc);
	}
	return (shaderProgram);
}

void Renderer_DrawPoint(float x, float y)
{
	GLfloat point[2] = {x, y};
	GLint screenSizeLocation = glGetUniformLocation(g_graphicsPipelineShader, "screenSize");
	GLint colorLocation = glGetUniformLocation(g_graphicsPipelineShader, "color");

	glUseProgram(g_graphicsPipelineShader);
		glUniform2f(screenSizeLocation, WIDTH, HEIGHT);
		glUniform3fv(colorLocation, 1, g_shaderColor);
		glBindVertexArray(g_pointVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, g_pointVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glDrawArrays(GL_POINTS, 0, 1);
			glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	glUseProgram(0);
}

void Renderer_DrawLine(float sx, float sy, float ex, float ey)
{	
	GLfloat lineVertices[2][2] = {
		{sx, sy},
		{ex, ey}
	};

	glUseProgram(g_graphicsPipelineShader);
		GLint screenSizeLocation = glGetUniformLocation(g_graphicsPipelineShader, "screenSize");
		GLint colorLocation = glGetUniformLocation(g_graphicsPipelineShader, "color");
		glUniform2f(screenSizeLocation, WIDTH, HEIGHT);
		glUniform3fv(colorLocation, 1, g_shaderColor);
		glBindVertexArray(g_lineVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, g_lineVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(lineVertices), lineVertices, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glDrawArrays(GL_LINES, 0, 2);
			glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	glUseProgram(0);
}

void	Renderer_Init(SDL_Window *window)
{
	g_context = SDL_GL_CreateContext(window);
	if (!g_context)
	{
		fprintf(stderr, "SDL failed to create OpenGL Context!");
		exit(EXIT_FAILURE);
	}
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
	{
		fprintf(stderr, "GLAD failed to initalize!");
		exit(EXIT_FAILURE);
	}
	g_graphicsPipelineShader = Renderer_CreateShader("./shaders/test_vert.glsl", "./shaders/test_frag.glsl");
	g_imageShader = Renderer_CreateShader("./shaders/image_vert.glsl", "./shaders/image_frag.glsl");

	glGenVertexArrays(1, &g_lineVertexArray);
	glGenBuffers(1, &g_lineVertexBuffer);

	glGenVertexArrays(1, &g_pointVertexArray);
	glGenBuffers(1, &g_pointVertexBuffer);

	glGenVertexArrays(1, &g_imageVertexArray);
	glGenBuffers(1, &g_imageVertexBuffer);
	glGenBuffers(1, &g_imageIndexBuffer);

	glGenVertexArrays(1, &g_rectVertexArray);
	glGenBuffers(1, &g_rectVertexBuffer);
	glGenBuffers(1, &g_rectIndexBuffer);

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("Shading language version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

void Renderer_DrawRect(float x, float y, float w, float h)
{
	GLfloat vertexArray[4][2] = {
		{x, y + h},
		{x + w, y + h},
		{x, y},
		{x + w, y}
	};

	GLuint vertexIndexes[2][3] = {
		{2, 0, 1},
		{3, 2, 1}
	};

	GLint screenSizeLocation = glGetUniformLocation(g_graphicsPipelineShader, "screenSize");
	GLint colorLocation = glGetUniformLocation(g_graphicsPipelineShader, "color");
	glUniform2f(screenSizeLocation, WIDTH, HEIGHT);
	glUniform3fv(colorLocation, 1, g_shaderColor);
	glUseProgram(g_graphicsPipelineShader);
		glBindVertexArray(g_pointVertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_rectIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndexes), vertexIndexes, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, g_rectVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	glUseProgram(0);
}

void Renderer_DrawImage(uint32_t glID, float x, float y, float z, float w, float h)
{
	GLfloat depth = ((1.0f / z) - (1.0f / 0.1f)) / ((1.0f / 16.0f) - (1.0f / 0.1f));
	GLfloat vertexArray[32] = {
		x, y + h, depth,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f,
		x + w, y + h, depth,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		x, y, depth,
		1.0f, 1.0f, 1.0f,
		0.0f, 0.0f,
		x + w, y, depth,
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f
	};

	GLuint vertexIndexes[2][3] = {
		{2, 0, 1},
		{3, 2, 1}
	};

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, glID);
	glUseProgram(g_imageShader);
		glUniform1i(glGetUniformLocation(g_imageShader, "tex"), 0);
		glUniform2f(glGetUniformLocation(g_imageShader, "screenSize"), (GLfloat)WIDTH, (GLfloat)HEIGHT);
		glUniform3fv(glGetUniformLocation(g_imageShader, "color"), 1, g_shaderColor);
		glBindVertexArray(g_imageVertexArray);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_imageIndexBuffer);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexIndexes), vertexIndexes, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, g_imageVertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertexArray), vertexArray, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, NULL);
			glEnableVertexAttribArray(1);
				glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GL_FLOAT) * 3));
			glEnableVertexAttribArray(2);
				glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GL_FLOAT) * 6));
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	glUseProgram(0);	
}

void	Renderer_Clear()
{
	SDL_GL_DeleteContext(g_context);
}

void	Renderer_PreDraw()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	glDisable(GL_CULL_FACE);
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void	Renderer_PostDraw()
{
	glDisable(GL_DEPTH_TEST);
	//glUseProgram(0);
}