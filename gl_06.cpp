#define GLEW_STATIC
#include <GL/glew.h>
#include "shprogram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <vector>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CubeModel.h"
#include "Textures.h"
#include "SkyBox.h"
#include "Water.h"
#include "Keyboard.h"

const GLuint WIDTH = 800, HEIGHT = 600;

// key buffer for camera movement
bool keys[1024];

GLfloat camX, camZ;

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 06", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);
		
		
		
		glfwSetKeyCallback(window, keyCallback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_06.vert", "gl_06.frag");
		// Set up cube model
		CubeModel cube(1.0f);
		SkyBox sky(100.0f);
		Water sea(50.0f,1000);

		Textures *t = Textures::getInstance();
		Keyboard k;
		
		glEnable(GL_DEPTH_TEST); // let's use z-buffer

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Calculate deltatime of current frame
			GLfloat currentFrame = (GLfloat) glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
			k.doMovement(deltaTime);

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Bind Textures using texture units

			theProgram.Use();
			GLuint modelLoc = glGetUniformLocation(theProgram.get_programID(), "model");
			GLuint viewLoc = glGetUniformLocation(theProgram.get_programID(), "view");
			GLuint projLoc = glGetUniformLocation(theProgram.get_programID(), "projection");
			GLuint time = glGetUniformLocation(theProgram.get_programID(), "time");
			GLuint period = glGetUniformLocation(theProgram.get_programID(), "period");
			GLuint length = glGetUniformLocation(theProgram.get_programID(), "length");
			GLuint water = glGetUniformLocation(theProgram.get_programID(), "water");

			k.isWater = false;

			glUniform1f(water, k.isWater);
			glUniform1f(time, currentFrame);
			glUniform1f(length,k.waveLength);
			glUniform1f(period, k.wavePeriod);

			// set perspective projection & pass it to GPU
			glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			GLfloat radius = 6.0f;
			camX = sin(k.xRotation) * radius;
			camZ = cos(k.xRotation) * radius;

			// set view transformation & pass it to GPU
			glm::mat4 view;
			//view = glm::lookAt(cameraPos, glm::vec3(0.0, 0.0, 0.0), cameraUp);

			view = glm::lookAt(glm::vec3(camX,2.0f, camZ), glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

			//t->setTexture("weiti");
			glm::mat4 trans;
			//cube.Draw(trans, modelLoc);
			t->setTexture("skybox");
			sky.Draw(trans, modelLoc);

			k.isWater = true;
			glUniform1f(water, k.isWater);

			t->setTexture("water");
			sea.Draw(trans, modelLoc);
			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}
