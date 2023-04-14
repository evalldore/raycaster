#include "map.h"
#include "renderer.h"

static GLuint	g_mapVertexArray = 0;
static GLuint	g_mapVertexBuffer = 0;
static GLuint	g_rayShader = 0;

static uint32_t		map_w = 16, map_h = 16;
static u_int32_t	map[][16] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	
};

static void Draw_Map(float x, float y, float a)
{
	uint32_t	coordX, coordY;

	Renderer_SetColor(0.4f, 0.4f, 1.0f);
	Renderer_DrawRect(0, 0, WIDTH, HEIGHT >> 1);
	Renderer_SetColor(0.2f, 0.2f, 0.2f);
	Renderer_DrawRect(0, HEIGHT >> 1, WIDTH, HEIGHT);

	for (coordY = 0; coordY < map_h; coordY++)
	{
		for (coordX = 0; coordX < map_h; coordX++)
		{
			if (map[coordY][coordX] == 1)
				Renderer_SetColor(0.0f, 0.0f, 0.0f);
			else
				Renderer_SetColor(1.0f, 1.0f, 1.0f);
			Renderer_DrawRect(coordX * TILE_SIZE + 1, coordY * TILE_SIZE + 1, TILE_SIZE - 2, TILE_SIZE - 2);
		}
	}

	Renderer_SetColor(1.0f, 0.0f, 0.0f);
	glPointSize(10);
	Renderer_DrawPoint(x * TILE_SIZE, y * TILE_SIZE);
	//direction
	Renderer_SetColor(0.0f, 0.0f, 1.0f);
	glLineWidth(2);
	Renderer_DrawLine(x * TILE_SIZE, y * TILE_SIZE, (x * TILE_SIZE) + cos(a) * 25, (y * TILE_SIZE) + sin(a) * 25);
}

static void	Draw_Ceiling()
{
	Renderer_SetColor(0.3f, 0.3f, 1.0f);
	Renderer_DrawRect(0.f, 0.f, WIDTH, HEIGHT >> 1);
}

static void	Draw_Floor()
{
	Renderer_SetColor(0.3f, 0.3f, 0.3f);
	Renderer_DrawRect(0.f, HEIGHT >> 1, WIDTH, HEIGHT);
}

int Map_GetTile(int x, int y)
{
	if (x >= 0 && x < map_w && y >= 0 && y < map_h)
		return (map[y][x]);
	return (0);
}

void Map_Init()
{
	glGenVertexArrays(1, &g_mapVertexArray);
	glGenBuffers(1, &g_mapVertexBuffer);
	g_rayShader = Renderer_CreateShader("./shaders/ray_vert.glsl", "./shaders/ray_frag.glsl");
}

void Map_Draw(float x, float y, float a)
{
	//Draw_Ceiling();
	//Draw_Floor();
	GLfloat	wallColor[3] = {1.0f, 0.0f, 0.0f};
	GLfloat txtXCoord = 0.0f;
	float planeAngle = rotate(a, DR * 90);
	fvec_t planeDir = {cos(planeAngle), sin(planeAngle)};
	fvec_t angleDir = {cos(a), sin(a)};
	int ray;
	int rayWidth = 8;
	int rayAmount = (WIDTH / rayWidth);
	u_int32_t rayHit = 0;
	GLfloat	*lineVertices = malloc((sizeof(GLfloat) * 14) * rayAmount);

	for(ray = 0; ray < rayAmount; ray++)
	{
		float cameraX = 2.0f * ((float)(ray) / (float)rayAmount) - 1.0f;
		fvec_t rayDir = {
			angleDir.x + (planeDir.x * 0.50f) * cameraX,
			angleDir.y + (planeDir.y * 0.50f) * cameraX,
		};
		ivec_t mapCheck = {(int)x, (int)y};
		fvec_t rayStep = {
			(rayDir.x == 0) ? INFINITY : fabs(1.0f / rayDir.x),
			(rayDir.y == 0) ? INFINITY : fabs(1.0f / rayDir.y),
		};
		fvec_t rayLength = {
			(((float)mapCheck.x + 1) - x) * rayStep.x,
			(((float)mapCheck.y + 1) - y) * rayStep.y
		};
		ivec_t vStep = {1, 1};
		if (rayDir.x < 0) 
		{
			vStep.x = -1;
			rayLength.x = (x - (float)mapCheck.x) * rayStep.x;
		}
		if (rayDir.y < 0) 
		{
			vStep.y = -1;
			rayLength.y = (y - (float)mapCheck.y) * rayStep.y;
		}
		bool tileFound = false;
		float distance = 0.0f;
		int	dof = 0;
		while (!tileFound && dof <= 16)
		{
			if (rayLength.x < rayLength.y) 
			{
				mapCheck.x += vStep.x;
				distance = rayLength.x;
				txtXCoord = (float)mapCheck.y - (y + rayDir.y * distance);
				rayLength.x += rayStep.x;
				//printf("tile: %d/%f\n", mapCheck.x, txtXCoord);
				wallColor[0] = fmax(1.0f - (distance / 11.0f), 0.0f);
				wallColor[1] = fmax(1.0f - (distance / 11.0f), 0.0f);
				wallColor[2] = fmax(1.0f - (distance / 11.0f), 0.0f);
				printf("%f\n", distance);
			} 
			else 
			{
				mapCheck.y += vStep.y;
				distance = rayLength.y;
				txtXCoord = (float)mapCheck.x - (x + rayDir.x * distance);
				rayLength.y += rayStep.y;
				wallColor[0] = fmax(1.0f - (distance / 11.0f), 0.0f) * 0.75f;
				wallColor[1] = fmax(1.0f - (distance / 11.0f), 0.0f) * 0.75f;
				wallColor[2] = fmax(1.0f - (distance / 11.0f), 0.0f) * 0.75f;
			}
			tileFound = (Map_GetTile(mapCheck.x, mapCheck.y) == 1);
			dof++;
		}

		if (tileFound)
		{
			float lineH = (float)(HEIGHT >> 1) - ((float)(HEIGHT >> 1) / distance);
			float lineO = HEIGHT - lineH;
			uint32_t rayVertIndex = rayHit * 14;
			//start position
			lineVertices[rayVertIndex] = (GLfloat)(ray * rayWidth);
			lineVertices[rayVertIndex + 1] = (GLfloat)lineO;
			//color start vertex
			lineVertices[rayVertIndex + 2] = wallColor[0];
			lineVertices[rayVertIndex + 3] = wallColor[1];
			lineVertices[rayVertIndex + 4] = wallColor[2];
			//start vertex coords;
			lineVertices[rayVertIndex + 5] = (float)txtXCoord;
			lineVertices[rayVertIndex + 6] = 1.0f;
			//end position
			lineVertices[rayVertIndex + 7] = (GLfloat)(ray * rayWidth);
			lineVertices[rayVertIndex + 8] = (GLfloat)lineH;
			//color end vertex
			lineVertices[rayVertIndex + 9] = wallColor[0];
			lineVertices[rayVertIndex + 10] = wallColor[1];
			lineVertices[rayVertIndex + 11] = wallColor[2];
			//vertex end coords
			lineVertices[rayVertIndex + 12] = (float)txtXCoord;
			lineVertices[rayVertIndex + 13] = 0.0f;
			rayHit++;
		}
	}

	texture_t *asset = Assets_Get(ASSET_WALLS);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, asset->glID);

	glUseProgram(g_rayShader);
		glUniform1i(glGetUniformLocation(g_rayShader, "tex"), 0);
		glUniform2f(glGetUniformLocation(g_rayShader, "screenSize"), (GLfloat)WIDTH, (GLfloat)HEIGHT);
		glBindVertexArray(g_mapVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, g_mapVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(GLfloat) * 14) * rayHit, lineVertices, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, NULL);
		glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (GLvoid*)(sizeof(GL_FLOAT) * 2));
		glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 7, (GLvoid*)(sizeof(GL_FLOAT) * 5));
		glLineWidth(rayWidth);
		glDrawArrays(GL_LINES, 0, rayHit * 2);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	glUseProgram(0);
	free(lineVertices);
}
