#include "Shaders.h"
//funtion for the reading the .shader file for the Device
std::string Shaders::readShaderFile(const std::string& filename) 
{
    //loadind the file from the Device
    std::ifstream file(filename);
    //checking the file is open or not
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }

    std::string shaderSource;
    std::string line;
    while (std::getline(file, line)) {
        shaderSource += line + "\n";
    }

    //closing the file
    file.close();
    //return the file
    return shaderSource;
}
//function for creating and compile the Shader
unsigned int Shaders::compileShader(unsigned int type, const std::string& source) 
{
    //creating the shader
    unsigned int shader = glCreateShader(type);
    //coverting the string file to char file(Due to the glShaderSource function takes only the char )
    const char* src = source.c_str();
    //getting the shader source
    glShaderSource(shader, 1, &src, nullptr);
    //compile the shader
    glCompileShader(shader);

    int success;
    char infoLog[512];
    //Getting the shaderiv and also the  COMPILE_STATUS using the enum GL_COMPILE_STATUS
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    //checking the it success or not
    if (!success) {
        //getting the info log after it is not success
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        //giving the error where the error was coming 
        std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
        //Deleting the Shader
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}
//funtion for the creating the ShaderProgram
unsigned int Shaders::CreateShaderProgram(std::string& vertexShader, std::string& fragmentShader) 
{ 
    //Creating ther vertex Shader
    unsigned int vshader = compileShader(GL_VERTEX_SHADER, vertexShader);
    //creating the fragment Shader
    unsigned int fshader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //creating the ShaderProgram
    shaderProgram = glCreateProgram();
    //Attaching the vertex Shader
    glAttachShader(shaderProgram, vshader);
    //Attaching the fragment Shader
    glAttachShader(shaderProgram, fshader);
    //Linking the Shader Program
    glLinkProgram(shaderProgram);
    // Check for shader compilation errors
    int success;
    char infoLog[512];
    //Getting the Programiv
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    //checking it success or not
    if (!success) {
        //grtting the shader program info if not success
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        //Deleting the vertex Shader
        glDeleteShader(vshader);
        //Deletting the fragment Shader
        glDeleteShader(fshader);
        //Deleting the ShaderProgram
        glDeleteProgram(shaderProgram);
        return -1;
    }
    //Deleting the vertex Shader
    glDeleteShader(vshader);
    //Deleting the fragment Shader
    glDeleteShader(fshader);
    return shaderProgram;
}
//funtion for setting the Uniform varaiable 
void Shaders::SetUniformLoaction4f(unsigned int shaderProgram, float r, float g, float b, float a) 
{
    //Getting the loaction from the Shader
    int location = glGetUniformLocation(shaderProgram, "_color");
    //Setting the color to the square
    glUniform4f(location, r, g, b, a);
}

void Shaders::SetunifromLoaction1f(unsigned int shaderProgram,float size) 
{ 
    //Getting the loaction from the Shader
    int location = glGetUniformLocation(shaderProgram, "_size");
    //Setting the size to the square
    glUniform1f(location, size);
}

void Shaders::SetunifromLoaction1i(unsigned int shaderProgram) 
{
    //Getting the loaction from the Shader
    int location = glGetUniformLocation(shaderProgram, "ourTexture");
    glUniform1i(location, 0);
}






