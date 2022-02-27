#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>
#include <string>
#include <filesystem>

#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "GLUtils.h"
#include "Utils.h"



#define numVAOs 1

GLuint renderingProgram;
GLuint vao[numVAOs];

GLuint CreateShaderProgram()
{
	std::string vPath = std::filesystem::current_path().append("src").append("shaders").append("vShader.vert").u8string();
	std::string fPath = std::filesystem::current_path().append("src").append("shaders").append("fShader.frag").u8string();


	std::cout << vPath << std::endl;
	std::string vSourceStr = ReadTextFile(vPath.c_str());
	std::string fSourceStr = ReadTextFile(fPath.c_str());
	//const char* vSource =
	//	"#version 430 \n"
	//	"void main() \n"
	//	"{ gl_Position = vec4(0.0, 0.0, 0.0, 1.0); }";
	//const char* fSource =
	//	"#version 430 \n"
	//	"out vec4 color; \n"
	//	"void main() \n"
	//	"{ color = vec4(1.0, 0.0, 1.0, 1.0); }";

	const char* vSource = vSourceStr.c_str();
	const char* fSource = fSourceStr.c_str();

	GLCall(GLuint vShader = glCreateShader(GL_VERTEX_SHADER));
	GLCall(GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER));

	GLCall(glShaderSource(vShader, 1, &vSource, NULL));
	GLCall(glShaderSource(fShader, 1, &fSource, NULL));
	GLCall(glCompileShader(vShader));
	GLCall(glCompileShader(fShader));

	GLCall(GLuint vfProgram = glCreateProgram());
	GLCall(glAttachShader(vfProgram, vShader));
	GLCall(glAttachShader(vfProgram, fShader));

	//after attaching the shaders you need to make sure they are compatible i.e. vertex shader and fragment shader in this case
	GLCall(glLinkProgram(vfProgram));

	return vfProgram;
}
void init(GLFWwindow* window)
{
	renderingProgram = CreateShaderProgram();
	GLCall(glGenVertexArrays(numVAOs, vao));
	GLCall(glBindVertexArray(vao[0]));
}

void display(GLFWwindow* window, double currentTime)
{
	GLCall(glClearColor(1.0, 0.0, 0.0, 1.0));
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glUseProgram(renderingProgram));
	GLCall(glPointSize(30.0f));
	GLCall(glDrawArrays(GL_POINTS, 0, 1));
}


int main()
{

	//initializing glfw
	if (!glfwInit())
		exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	GLFWwindow* window = glfwCreateWindow(1280, 760, "Simple App", NULL, NULL);
	glfwMakeContextCurrent(window);
	//initializing glew
	if (glewInit() != GLEW_OK)
		exit(EXIT_FAILURE);

	glfwSwapInterval(1);
	init(window);

	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");

	bool showDemoWindow = false;

	//rendering the frame buffer to the window
	while (!glfwWindowShouldClose(window))
	{
		//Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		if (showDemoWindow)
			ImGui::ShowDemoWindow(&showDemoWindow);
		else
		{
			//insert your code in here 
			{
				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
				ImGui::Text("This is some useful text.");
				ImGui::End();
			}
		}
		ImGui::Render();
		display(window, glfwGetTime());
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	//destroying glfw
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}