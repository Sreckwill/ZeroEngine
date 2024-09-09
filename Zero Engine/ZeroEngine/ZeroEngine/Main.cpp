#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <sstream>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl2.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shaders.h"
#include "Textures.h"
#include "Camera.h"
void showFPS(GLFWwindow* window);
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
            -0.5f, -0.5f, 0.0f, 0.0f,
             0.5f, -0.5f, 1.0f, 0.0f,
             0.5f,  0.5f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 1.0f
        };

        //Indices of the Square
        unsigned int indices[] = {
            0, 1, 2,
            0, 3, 2
        };

        //Creating the Object for the Vertex Buffer
        VertexBuffer vb;
        //Bind the Vertex Buffer
        vb.Bind();

        //Creating the Object for the Vertex Array
        VertexArray va;
        //Bind the Vertex Array
        va.Bind();

        //Giving the Data to the Buffer
        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
        //VertexAttribPointer
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
        //Enableing Vertex Attrib Array
        glEnableVertexAttribArray(0);
        //VertexAttribPointer
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(2*sizeof(float)));
        //Enableing Vertex Attrib Array
        glEnableVertexAttribArray(1);
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

        //unbinding the Vertex Buffer and Array
        vb.UnBind();
        va.UnBind();

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330"); 

        Textures textures("Texturs/solor.jpg");
        
        Camera camera;
        bool cameraEnabled = true; // Boolean to track if the camera is enabled
        // Inside your main loop
        while (!glfwWindowShouldClose(window)) {
            showFPS(window);
            float deltaTime = 0.0f;
            // Start ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Handle camera input only if cameraEnabled is true
            if (cameraEnabled) {
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                    camera.ProcessKeyboard(GLFW_KEY_W, deltaTime);
                }

                if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                    camera.ProcessKeyboard(GLFW_KEY_S, deltaTime);
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                    camera.ProcessKeyboard(GLFW_KEY_A, deltaTime);
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                    camera.ProcessKeyboard(GLFW_KEY_D, deltaTime);
            }
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(1.0f, 0.5f, 1.0f, 0.5f);

            // Bind vertex array, vertex Buffer and shader program
            vb.Bind();
            va.Bind();
            shaders.UseProgram(shaderProgram);

            //Bind the Texture
            textures.ActiveTexure(GL_TEXTURE0);
            textures.bind();

            // Draw OpenGL geometry
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            // Pass color value to shader
            shaders.SetUniformLoaction4f(shaderProgram, color[0], color[1], color[2], color[3]);
            //Pass size value to shader
            shaders.SetunifromLoaction1f(shaderProgram, size);
            //Pass the Texture
            shaders.SetunifromLoaction1i(shaderProgram);

            glm::mat4 view = camera.GetViewMatrix();
            // ImGui rendering
            ImGui::Begin("Window");
            ImGui::Text("hello");
            ImGui::ColorEdit4("Color", color);
            ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
            // Add button to enable/disable the camera
            if (ImGui::Button("Toggle Camera")) {
                cameraEnabled = !cameraEnabled;
            }
            ImGui::Text("Camera is %s", cameraEnabled ? "ON" : "OFF");
            ImGui::End();
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Unbind resources
            va.UnBind();;
            vb.UnBind();
            shaders.UseProgram(0);

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
// Function to calculate and display FPS
void showFPS(GLFWwindow* window)
{
    static double previousSeconds = 0.0;
    static int frameCount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime();
    elapsedSeconds = currentSeconds - previousSeconds;

    if (elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        double fps = (double)frameCount / elapsedSeconds;
        double msPerFrame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed << "Game World" << "  " << "FPS: "
            << fps << "  " << "Frame Time: " << msPerFrame << " (ms)";
        glfwSetWindowTitle(window, outs.str().c_str());
        frameCount = 0;
    }
    frameCount++;
}

