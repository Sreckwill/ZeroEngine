#include "Shaders.h"

//funtion for the reading the .shader file for the Device
std::string Shaders::readShaderFile(const std::string& filename) 
{
    //loadind the file from the Device
    std::ifstream file(filename);
    std::string shaderSource;
    std::string line;
    try {
        //checking the file is open or not
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return "";
        }
        while (std::getline(file, line)) {
            shaderSource += line + "\n";
        }
        //closing the file
        file.close();
    }
    catch (std::exception ex)
    {
        std::cerr << "Error reading shader filename!" << std::endl;
    }
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
    //Getting the shaderiv and also the  COMPILE_STATUS using the enum GL_COMPILE_STATUS
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    //checking the it success or not
    if (!success) {
        int length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

        // The length includes the NULL character
        std::string errorLog(length, ' ');  // Resize and fill with space character
        glGetShaderInfoLog(shader, length, &length, &errorLog[0]);

        std::cerr << "Shader compilation failed:\n" << errorLog << std::endl;

        // Deleting the Shader to clean up resources
        glDeleteShader(shader);
        return 0;  // or appropriate error code
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
//Getting the UnifromLocation
int Shaders::GetUnifromLocation(const char* name)
{
    std::map<string, GLint>::iterator it = UniformLocations.find(name);

    // Only need to query the shader program IF it doesn't already exist.
    if (it == UniformLocations.end())
    {
        // Find it and add it to the map
        UniformLocations[name] = glGetUniformLocation(shaderProgram, name);
    }
    // Return it
    return UniformLocations[name];
}

void Shaders::UseProgram(unsigned int shaderProgram)
{
    glUseProgram(shaderProgram);
}

void Shaders::SetUniformLoaction(unsigned int shaderProgram, float r, float g, float b, float a, const  char* name)
{
    //Getting the loaction from the Shader
    int location = GetUnifromLocation(name);
    //Setting the color to the square
    glUniform4f(location, r, g, b, a);
}

void Shaders::SetUnifromLoaction(unsigned int shaderProgram,const  char* name)
{
    //Getting the loaction from the Shader
    int location = GetUnifromLocation(name);
    glUniform1i(location, 0);
}

void Shaders::SetUnifromLoaction(unsigned int shaderProgram, float size, const  char* name)
{
    //Getting the loaction from the Shader
    int location = GetUnifromLocation(name);
    //Setting the size to the square
    glUniform1f(location, size);
}

void Shaders::SetunifromLoaction(unsigned int shaderPrgram, const glm::vec2& v, const  char* name)
{
    //Getting the loaction from the Shader
    int location = GetUnifromLocation(name);
    //Setting the size to the square
    glUniform2f(location, v.x, v.y);
}

void Shaders::SetunifromLoaction(unsigned int shaderPrgram, const glm::vec3& v, const  char* name)
{
    //Getting the loaction from the Shader
    int location = GetUnifromLocation(name);
    //Setting the size to the square
    glUniform3f(location, v.x, v.y, v.z);
}

void Shaders::SetunifromLoaction(unsigned int shaderPrgram, const glm::vec4& v, const  char* name)
{
    //Getting the loaction from the Shader
    int location = GetUnifromLocation(name);
    //Setting the size to the square
    glUniform4f(location, v.x, v.y, v.z, v.w);
}

void Shaders::SetunifromLoaction(unsigned int shaderPrgram, const glm::mat4& v, const  char* name)
{
    //Getting the loaction from the Shader
    int location = GetUnifromLocation(name);
    //Setting the size to the square
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(v));
}






