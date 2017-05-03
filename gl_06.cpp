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

const GLuint WIDTH = 800, HEIGHT = 600;

// key buffer for camera movement
bool keys[1024];

GLfloat camX, camZ;
float xRotation = 0.0f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

// Camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
GLfloat pitch = 0.0f; // elewacja
const GLfloat pitch_max = 80.0f, pitch_min = -80.0f;

GLfloat yaw = 0.0f; // azymut
const GLfloat yaw_max = 360.0f, yaw_min = 0.0f;

glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

void do_movement()
{
	if (keys[GLFW_KEY_A])
		xRotation -= 0.01f;
	if (keys[GLFW_KEY_D])
		xRotation += 0.01f;
	// Camera controls
	GLfloat cameraSpeed = 25.0f * deltaTime;
	if (keys[GLFW_KEY_UP])
		if ((pitch += cameraSpeed) > pitch_max)
			pitch = pitch_max;
	if (keys[GLFW_KEY_DOWN])
		if ((pitch -= cameraSpeed) < pitch_min)
			pitch = pitch_min;
	if (keys[GLFW_KEY_LEFT])
		if ((yaw -= cameraSpeed) < yaw_min)
			yaw += yaw_max;
	if (keys[GLFW_KEY_RIGHT])
		if ((yaw += cameraSpeed) > yaw_max)
			yaw -= yaw_max;
	// cout << "Yaw: " << yaw << "  pitch: " << pitch << endl;
}



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
		glfwSetKeyCallback(window, key_callback);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glViewport(0, 0, WIDTH, HEIGHT);

		// Build, compile and link shader program
		ShaderProgram theProgram("gl_06.vert", "gl_06.frag");
		ShaderProgram waterProgram("water.vert", "gl_06.frag");
		// Set up cube model
		CubeModel cube(1.0f);
		
		SkyBox sky(100.0f);

		Water sea(50.0f, 100);


		Textures *t = Textures::getInstance();


		bool isWater = false;
		float waveLength = 10;
		float wavePeriod = 4;
		

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
			do_movement();

			
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

			isWater = false;

			glUniform1f(water, isWater);
			glUniform1f(time, currentFrame);
			glUniform1f(length,waveLength);
			glUniform1f(period, wavePeriod);

			// set perspective projection & pass it to GPU
			glm::mat4 projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

			GLfloat radius = 6.0f;
			camX = sin(xRotation) * radius;
			camZ = cos(xRotation) * radius;

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

			isWater = true;
			glUniform1f(water, isWater);

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
