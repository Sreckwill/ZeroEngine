#include "Shaders.h"

std::string Shaders::readShaderFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "";
    }

    std::string shaderSource;
    std::string line;
    while (std::getline(file, line)) {
        shaderSource += line + "\n";
    }

    file.close();

    return shaderSource;
}

unsigned int Shaders::compileShader(unsigned int type, const std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader compilation failed:\n" << infoLog << std::endl;
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

unsigned int Shaders::CreateShaderProgram(std::string& vertexShader, std::string& fragmentShader)
{
    unsigned int vshader = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fshader = compileShader(GL_FRAGMENT_SHADER, fragmentShader);


    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vshader);
    glAttachShader(shaderProgram, fshader);
    glLinkProgram(shaderProgram);
    // Check for shader compilation errors
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        glDeleteShader(vshader);
        glDeleteShader(fshader);
        glDeleteProgram(shaderProgram);
        return -1;
    }
    glDeleteShader(vshader);
    glDeleteShader(fshader);
    return shaderProgram;
}

void Shaders::SetUniformLoaction4f(unsigned int shaderProgram, float r, float g, float b, float a)
{
    int Loaction = glGetUniformLocation(shaderProgram, "_Color");
    glUniform4f(Loaction, r,g,b,a);
}