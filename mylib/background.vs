#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
uniform float zoom;
uniform vec2 offset;
uniform mat4 model;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = model * vec4((aPos-offset)*zoom, 0.0, 1.0);
    ourColor = vec3(1.0, 1.0, 1.0);
    TexCoord = aTexCoord;
}