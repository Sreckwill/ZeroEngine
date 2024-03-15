#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shaders.h"


int main() {

    //GLFW Init
    if (!glfwInit()) {
        return -1;
    }
    //Creating Window
    GLFWwindow* window = glfwCreateWindow(600, 600, "Game Window", nullptr, nullptr);
    //Checking the winodw is null or not
    if (!window) {
        std::cerr << "Error loading the Window!...";
        glfwTerminate();
        return -1;
    }
    //making the window as the current Contex
    glfwMakeContextCurrent(window);

    //Checking the GLEW Init
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error Loading GLEW!...";
        glfwTerminate();
        return -1;
    }
    
    {
        //Positions of the Sqaure
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f, 0.5f
        };

        //Indices of the Square
        unsigned int indices[] = {
            0, 1, 2,
            0, 3, 2
        };

        //Vertex Arrat 
        unsigned int vao;
        //Generating the Vertex Array
        glGenVertexArrays(1, &vao);
        //Binding the Vertex Array
        glBindVertexArray(vao);

        //Creating the Object for the Vertex Array
        VertexBuffer vb;
        //Bind the Vertex Array
        vb.Bind();

        //Giving the Data to the Buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        //VertexAttribPointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
        //Enableing Vertex Attrib Array
        glEnableVertexAttribArray(0);

        //Creating the IndexBuffer Object
        IndexBuffer ib;
        //Binding the IndexBuffer
        ib.Bind();
        //Giving the Data to the Buffer
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

       //Creating the Shaders class Object
        Shaders shaders;
        //Getting the vertexShader code from the file
        std::string filename = "vertexShader.shader";
        //Storing the shaders.readShaderFile(filename) funtion to the string
        std::string shaderSource = shaders.readShaderFile(filename);
        //checking if it is empty or not
        if (shaderSource.empty()) {
            std::cerr << "Failed to read vertex shader source." << std::endl;
            return -1;
        }
        //Getting the fragmentShader code from the file
        std::string filename1 = "fragmentShader.shader";
        //Storing the shaders.readShaderFile(filename) funtion to the string
        std::string shaderSource1 = shaders.readShaderFile(filename1);
        //checking if it is empty or not
        if (shaderSource1.empty()) {
            std::cerr << "Failed to read fragment shader source." << std::endl;
            return -1;
        }
        //String the shaders.CreateShaderProgram(shaderSource, shaderSource1); fuction to the unsigned int shaderProgram 
        unsigned int shaderProgram = shaders.CreateShaderProgram(shaderSource, shaderSource1);
        //use the shaderProgra,
        glUseProgram(shaderProgram);
        //Setting the Color of the Square by Uniform varaiable
        shaders.SetUniformLoaction4f(shaderProgram, 0.1f, 0.1f, 1.0f, 1.0f);
        //unbinding the Vertex Array
        glBindVertexArray(0);
        //Loop for the rendereing the Square
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 0.5f, 1.0f, 0.5f);
            glBindVertexArray(vao);
            glUseProgram(shaderProgram);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
            glBindVertexArray(0);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }
    //Termating the GLFW
    glfwTerminate();
    return 0;
}
