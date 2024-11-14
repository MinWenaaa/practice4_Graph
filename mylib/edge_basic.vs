#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in bool walked;
out vec3 fragColor;

void main() {
	gl_Position = vec4(pos, 0.0, 1.0);
	fragColor = walked ? (0.8f, 0.6f, 0.6f, 1.0f):(0.1f, 0.0f, 0.0f, 1.0f);
}