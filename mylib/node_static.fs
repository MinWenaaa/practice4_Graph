#version 330 core
flat in int color;
out vec4 FragColor;

void main() {
	switch(color) {
	case 0:
		FragColor = vec4(0.8, 0.6, 0.6, 1.0);
		break;
	case 1:
		FragColor = vec4(0.6, 0.8, 0.6, 1.0);
		break;
	case 2:
		FragColor = vec4(0.6, 0.6, 0.8, 1.0);
		break;
	default:
		FragColor = vec4(0.6, 0.6, 0.6, 1.0);
		break;
	}
}