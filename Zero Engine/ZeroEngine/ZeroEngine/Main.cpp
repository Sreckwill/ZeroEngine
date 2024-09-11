#include <iostream>
#include <sstream>
#include <string>
#include "GL/glew.h"	
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl2.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "Shaders.h"
#include "Textures.h"
#include "Camera.h"
#include "Mesh.h"


// Global Variables
const char* APP_TITLE = "Game Engine";
int gWindowWidth = 1024;
int gWindowHeight = 768;
GLFWwindow* gWindow = NULL;
bool gWireframe = false;
bool ghelp = false;

FPSCamera fpsCamera(glm::vec3(0.0f, 3.0f, 10.0f));
const double ZOOM_SENSITIVITY = -3.0;
const float MOVE_SPEED = 5.0; // units per second
const float MOUSE_SENSITIVITY = 0.1f;

// Function prototypes
void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void glfw_onFramebufferSize(GLFWwindow* window, int width, int height);
void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY);
void update(double elapsedTime);
void showFPS(GLFWwindow* window);
bool initOpenGL();

int main()
{
	if (!initOpenGL())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return -1;
	}

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

	// Load meshes and textures
	const int numModels = 4;
	Mesh mesh[numModels];
	Textures texture[numModels];

	mesh[0].loadOBJ("models/crate.obj");
	mesh[1].loadOBJ("models/woodcrate.obj");
	mesh[2].loadOBJ("models/robot.obj");
	mesh[3].loadOBJ("models/floor.obj");

	texture[0].LoadTexture("textures/crate.jpg", true);
	texture[1].LoadTexture("textures/woodcrate_diffuse.jpg", true);
	texture[2].LoadTexture("textures/robot_diffuse.jpg", true);
	texture[3].LoadTexture("textures/tile_floor.jpg", true);

	// Model positions
	glm::vec3 modelPos[] = {
		glm::vec3(-2.5f, 1.0f, 0.0f),	// crate1
		glm::vec3(2.5f, 1.0f, 0.0f),	// crate2
		glm::vec3(0.0f, 0.0f, -2.0f),	// robot
		glm::vec3(0.0f, 0.0f, 0.0f)		// floor
	};

	// Model scale
	glm::vec3 modelScale[] = {
		glm::vec3(1.0f, 1.0f, 1.0f),	// crate1
		glm::vec3(1.0f, 1.0f, 1.0f),	// crate2
		glm::vec3(1.0f, 1.0f, 1.0f),	// robot
		glm::vec3(10.0f, 1.0f, 10.0f)	// floor
	};

	double lastTime = glfwGetTime();
	// Initialize ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(gWindow, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	// Rendering loop
	while (!glfwWindowShouldClose(gWindow))
	{
		showFPS(gWindow);

		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;

		// Poll for and process events
		glfwPollEvents();
		update(deltaTime);
		// Start the ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		// ImGui UI code
		ImGui::Begin("Menu"); // Main Menu

		// Child window for "Settings"
		ImGui::BeginChild("Settings", ImVec2(0, 100), true); // Create a child with height of 100
		ImGui::Text("Settings");
		ImGui::Checkbox("Wireframe Mode", &gWireframe); // Settings-related checkbox
		ImGui::EndChild(); // End "Settings" child

		ImGui::Spacing(); // Optional: Adds spacing between the two child windows

		// Child window for "Help"
		ImGui::BeginChild("Help", ImVec2(0, 100), true); // Create another child for "Help"
		ImGui::Text("Help");
		ImGui::Checkbox("Help", &ghelp); // Help-related checkbox
		ImGui::EndChild(); // End "Help" child

		
		ImGui::End(); // End "Menu"
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 model(1.0), view(1.0), projection(1.0);

		// Create the View matrix
		view = fpsCamera.getViewMatrix();

		// Create the projection matrix
		projection = glm::perspective(glm::radians(fpsCamera.getFOV()), (float)gWindowWidth / (float)gWindowHeight, 0.1f, 200.0f);

		// Must be called BEFORE setting uniforms because setting uniforms is done
		// on the currently active shader program.
		shaders.UseProgram(shaderProgram);

		// Pass the matrices to the shader
		shaders.SetunifromLoaction(shaderProgram, view, "view");
		shaders.SetunifromLoaction(shaderProgram, projection, "projection");
		

		// Render the scene
		for (int i = 0; i < numModels; i++)
		{
			model = glm::translate(glm::mat4(1.0), modelPos[i]) * glm::scale(glm::mat4(1.0), modelScale[i]);
			shaders.SetunifromLoaction(shaderProgram, model, "model");

			texture[i].Bind(0);		// set the texture before drawing.  Our simple OBJ mesh loader does not do materials yet.
			mesh[i].draw();			// Render the OBJ mesh
			texture[i].UnBind(0);
			
		}
		// Rendering ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		// Swap front and back buffers
		glfwSwapBuffers(gWindow);

		lastTime = currentTime;
	}
	// Cleanup ImGui
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();

	return 0;
}


bool initOpenGL()
{
	// Intialize GLFW 
	// GLFW is configured.  Must be called before calling any GLFW functions
	if (!glfwInit())
	{
		// An error occured
		std::cerr << "GLFW initialization failed" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);	// forward compatible with newer versions of OpenGL as they become available but not backward compatible (it will not run on devices that do not support OpenGL 3.3


	// Create an OpenGL 3.3 core, forward compatible context window
	gWindow = glfwCreateWindow(gWindowWidth, gWindowHeight, APP_TITLE, NULL, NULL);
	if (gWindow == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	// Make the window's context the current one
	glfwMakeContextCurrent(gWindow);

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return false;
	}

	// Set the required callback functions
	glfwSetKeyCallback(gWindow, glfw_onKey);
	glfwSetFramebufferSizeCallback(gWindow, glfw_onFramebufferSize);
	glfwSetScrollCallback(gWindow, glfw_onMouseScroll);

	// Hides and grabs cursor, unlimited movement
	glfwSetInputMode(gWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	// Define the viewport dimensions
	glViewport(0, 0, gWindowWidth, gWindowHeight);
	glEnable(GL_DEPTH_TEST);



	return true;
}


void glfw_onKey(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		gWireframe = !gWireframe;
		if (gWireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
	{
		ghelp = !ghelp;
		if (ghelp)
			std::cout << "Enter";
		else
			std::cout << "Exit";
	}
	
}

void glfw_onFramebufferSize(GLFWwindow* window, int width, int height)
{
	gWindowWidth = width;
	gWindowHeight = height;
	glViewport(0, 0, gWindowWidth, gWindowHeight);
}

void glfw_onMouseScroll(GLFWwindow* window, double deltaX, double deltaY)
{
	double fov = fpsCamera.getFOV() + deltaY * ZOOM_SENSITIVITY;

	fov = glm::clamp(fov, 1.0, 120.0);

	fpsCamera.setFOV((float)fov);
}

void update(double elapsedTime)
{
	// Camera orientation
	double mouseX, mouseY;

	// Get the current mouse cursor position delta
	glfwGetCursorPos(gWindow, &mouseX, &mouseY);

	// Rotate the camera the difference in mouse distance from the center screen.  Multiply this delta by a speed scaler
	fpsCamera.rotate((float)(gWindowWidth / 2.0 - mouseX) * MOUSE_SENSITIVITY, (float)(gWindowHeight / 2.0 - mouseY) * MOUSE_SENSITIVITY);

	// Clamp mouse cursor to center of screen
	glfwSetCursorPos(gWindow, gWindowWidth / 2.0, gWindowHeight / 2.0);

	// Camera FPS movement

	// Forward/backward
	if (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getLook());
	else if (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getLook());

	// Strafe left/right
	if (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getRight());
	else if (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getRight());

	// Up/down
	if (glfwGetKey(gWindow, GLFW_KEY_Z) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * fpsCamera.getUp());
	else if (glfwGetKey(gWindow, GLFW_KEY_X) == GLFW_PRESS)
		fpsCamera.move(MOVE_SPEED * (float)elapsedTime * -fpsCamera.getUp());
}

void showFPS(GLFWwindow* window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;
	double currentSeconds = glfwGetTime(); // returns number of seconds since GLFW started, as double float

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text updates to 4 times per second
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		// The C++ way of setting the window title
		std::ostringstream outs;
		outs.precision(3);	// decimal places
		outs << std::fixed
			<< APP_TITLE << "    "
			<< "FPS: " << fps << "    "
			<< "Frame Time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		// Reset for next average.
		frameCount = 0;
	}

	frameCount++;
}