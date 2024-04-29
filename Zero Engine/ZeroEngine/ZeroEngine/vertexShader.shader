#version 330 core
layout(location = 0) in vec2 pos;
layout(location=1) in vec2 aTexCoord;

uniform float _size;
out vec2 TexCoord;
void main() {
    gl_Position = vec4(_size*pos.x, _size*pos.y, 0.0, 1.0);
    TexCoord=aTexCoord;
}
