#version 410 core
out vec4 frag_color;
in vec3 vert_color;
in vec2 vert_texCoord;
//uniform vec3 color;
uniform sampler2D tex;

void main()
{
	frag_color = texture(tex, vert_texCoord) * vec4(vert_color, 1.0f);
}