#version 330 core
out vec4 FragColor;
uniform vec4 _color; // Use 'color' instead of '_Color'
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{
    //FragColor = _color; // Use 'color' instead of '_Color'
    FragColor=texture(ourTexture,TexCoord);//for loading texture
}
