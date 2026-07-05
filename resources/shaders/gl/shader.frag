#version 430 core

in vec3 f_color;
in vec2 tex_coord;

out vec4 FragColor;

layout(binding = 0) uniform sampler2D uTexture;

void main() {
    vec4 color = texture(uTexture, tex_coord) * vec4(f_color, 1.0f);
    FragColor = color;
}

