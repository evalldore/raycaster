#version 410 core
uniform vec2 screenSize;
layout(location=0) in vec2 position;

void main()
{
	vec2 normalized = vec2(position.x / screenSize.x * 2.0 - 1.0, (screenSize.y - position.y) / screenSize.y * 2.0 - 1.0);
	gl_Position = vec4(normalized, 0.0, 1.0);
}