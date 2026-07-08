#version 450

layout(location = 0) in vec3 v_pos;
layout(location = 1) in vec2 v_uv;
layout(location = 2) in vec3 v_color;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 texCoord;

void main() 
{
    texCoord = v_uv;
	fragColor = vec4(v_color, 1.0f);

	gl_Position = vec4(v_pos, 1.0f);
}
