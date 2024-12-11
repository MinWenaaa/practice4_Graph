#version 330 core
layout(location = 0) in vec2 pos;
layout(location = 1) in int color;
flat out int fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	fragColor = color;
}
