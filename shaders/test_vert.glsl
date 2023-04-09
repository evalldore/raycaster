#version 410 core

layout(location=0) in vec3 position;
layout(location=1) in vec3 colors;
out vec3 v_colors;

void main()
{
	v_colors = colors;
	gl_Position = vec4(position.x, position.y, position.z, 1.0f);
}