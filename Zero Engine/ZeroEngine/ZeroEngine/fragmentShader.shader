#version 330 core
out vec4 FragColor;
uniform vec4 _color; // Use 'color' instead of '_Color'
void main()
{
    FragColor = _color; // Use 'color' instead of '_Color'
}
