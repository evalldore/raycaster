#version 410 core
uniform vec2 screenSize;
layout (location=0) in vec3 position;
layout (location=1) in vec3 color;
layout (location=2) in vec2 texCoord;
out vec3 vert_color;
out vec2 vert_texCoord;

void main()
{
	vec2 normalized = vec2(position.x / screenSize.x * 2.0 - 1.0, (screenSize.y - position.y) / screenSize.y * 2.0 - 1.0);
	gl_Position = vec4(normalized, position.z, 1.0);
	vert_color = color;
	vert_texCoord = texCoord;
}