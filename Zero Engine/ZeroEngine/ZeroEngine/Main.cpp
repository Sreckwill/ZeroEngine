#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include <fstream>
#include <string>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
std::string readShaderFile(const std::string& filename) {
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
int main() {
	

	std::string filename = "vertexShader.shader";
	std::string shaderSource = readShaderFile(filename);
	if (!shaderSource.empty()) {
		// Do something with the shader source code
		std::cout << "VertexShader:\n" << shaderSource << std::endl;
	}

	std::string filename1 = "fragmentShader.shader";
	std::string shaderSource1 = readShaderFile(filename1);
	if (!shaderSource1.empty()) {
		// Do something with the shader source code
		std::cout << "Fragment Shader:\n" << shaderSource1 << std::endl;
	}


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
                0 ,3, 2
            };

            unsigned int vao;
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            VertexBuffer vb;
            glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
            glEnableVertexAttribArray(0);

            IndexBuffer ib;
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            vb.UnBind();
            glBindVertexArray(0);




            while (!glfwWindowShouldClose(window)) {
                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(1.0f, 0.5f, 1.0f, 0.5f);
                glBindVertexArray(vao);
                vb.Bind();
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
                vb.UnBind();
                glBindVertexArray(0);
                glfwSwapBuffers(window);
                glfwPollEvents();
            }
        }
	glfwTerminate();

	return 0;
}