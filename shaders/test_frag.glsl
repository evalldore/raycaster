#version 410 core
in vec3 v_colors;
out vec4 color;

void main()
{
	color = vec4(v_colors.r, v_colors.g, v_colors.b, 1.0f);
}