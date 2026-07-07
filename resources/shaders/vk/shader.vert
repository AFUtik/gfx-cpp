#version 450

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec3 v_color;

layout(location = 0) out vec4 fragColor;

void main() 
{
	fragColor = vec4(v_color, 1.0f);

	gl_Position = vec4(v_pos, 1.0f);
}
