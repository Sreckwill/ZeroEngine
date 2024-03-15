#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shaders.h"


int main() {

    
    if (!glfwInit()) {
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(600, 600, "Game Window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Error loading the Window!...";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Error Loading GLEW!...";
        glfwTerminate();
        return -1;
    }

    {
        float positions[] = {
            -0.5f, -0.5f,
             0.5f, -0.5f,
             0.5f,  0.5f,
            -0.5f, 0.5f
        };

        unsigned int indices[] = {
            0, 1, 2,
            0, 3, 2
        };

        unsigned int vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        VertexBuffer vb;
        vb.Bind();
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
        glEnableVertexAttribArray(0);

        IndexBuffer ib;
        ib.Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

       
        Shaders shaders;

        std::string filename = "vertexShader.shader";
        std::string shaderSource = shaders.readShaderFile(filename);
        if (shaderSource.empty()) {
            std::cerr << "Failed to read vertex shader source." << std::endl;
            return -1;
        }

        std::string filename1 = "fragmentShader.shader";
        std::string shaderSource1 = shaders.readShaderFile(filename1);
        if (shaderSource1.empty()) {
            std::cerr << "Failed to read fragment shader source." << std::endl;
            return -1;
        }

        unsigned int shaderProgram = shaders.CreateShaderProgram(shaderSource, shaderSource1);
        glUseProgram(shaderProgram);
        shaders.SetUniformLoaction4f(shaderProgram, 0.1f, 0.1f, 1.0f, 1.0f);

        glBindVertexArray(0);

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
    glfwTerminate();

    return 0;
}
