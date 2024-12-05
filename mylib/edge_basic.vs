#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in int color;
flat out int fragColor;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);
	fragColor = color;
}