#version 330 core
layout(location = 0) in vec2 pos;
uniform float _size;

void main() {
    gl_Position = vec4(_size*pos.x, _size*pos.y, 0.0, 1.0);
}
