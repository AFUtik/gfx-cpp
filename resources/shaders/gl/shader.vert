#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUv;
layout (location = 2) in vec3 aColor;

out vec3 f_color;
out vec2 tex_coord;

void main() {
    f_color   = aColor;
    tex_coord = aUv;

    gl_Position = vec4(aPos, 1.0);
}
