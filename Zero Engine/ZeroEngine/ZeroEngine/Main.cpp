#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl2.h"
#include "ImGui/imgui_impl_opengl3.h"
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

        float color[4] = { 0.5f, 0.5f, 1.0f, 1.0f };
        //Setting the Color of the Square by Uniform varaiable
         //or
        //  //Pass color value to shader
        shaders.SetUniformLoaction4f(shaderProgram, color[0], color[1], color[2], color[3]);

        //size for the square
        float size = 1.0f;
        //Setting the Size of the Square by Uniform varaiable 
        //or
        //  //Pass size value to shader
        shaders.SetunifromLoaction1f(shaderProgram, size);
        //unbinding the Vertex Array
        glBindVertexArray(0);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330"); 

       
       
        // Inside your main loop
        while (!glfwWindowShouldClose(window)) {
            // Start ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 0.5f, 1.0f, 0.5f);

            // Bind vertex array and shader program
            glBindVertexArray(vao);
            glUseProgram(shaderProgram);

            // Draw OpenGL geometry
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            // Pass color value to shader
            shaders.SetUniformLoaction4f(shaderProgram, color[0], color[1], color[2], color[3]);
            //Pass size value to shader
            shaders.SetunifromLoaction1f(shaderProgram, size);

            // ImGui rendering
            ImGui::Begin("Window");
            ImGui::Text("hello");
            ImGui::ColorEdit4("Color", color);
            ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
            ImGui::End();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Unbind resources
            glBindVertexArray(0);
            glUseProgram(0);

            // Swap buffers and poll events
            glfwSwapBuffers(window);
            glfwPollEvents();

            // Check for OpenGL errors
            GLenum error = glGetError();
            if (error != GL_NO_ERROR) {
                std::cerr << "OpenGL error: " << error << std::endl;
            }
        }

    }
    //Destroying or shadown the ImGui
    ImGui_ImplGlfw_Shutdown();
    ImGui_ImplOpenGL3_Shutdown();   
    ImGui::DestroyContext();

    //Termating the GLFW
    glfwTerminate();
    return 0;
}
