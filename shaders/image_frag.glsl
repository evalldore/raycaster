#version 410 core
out vec4 frag_color;
in vec3 vert_color;
in vec2 vert_texCoord;
uniform vec3 color;
uniform sampler2D tex;

float near = 0.1; 
float far  = 100.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	vec4 pixel = texture(tex, vert_texCoord);
	if (pixel.r == 1.0 && pixel.b == 1.0)
		discard;
	frag_color = pixel * vec4(vert_color, 1.0f);
	//float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
	//frag_color = vec4(vec3(depth), 1.0);
}