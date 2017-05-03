
#include <GLFW/glfw3.h>
#include "Keyboard.h"


Keyboard::Keyboard()
{
}
void Keyboard::doMovement(GLfloat deltaTime){
	// kamera rotation
	if (keys[GLFW_KEY_A])
		xRotation -= d;
	if (keys[GLFW_KEY_D])
		xRotation += d;
	//  fala dlugosc
	if (keys[GLFW_KEY_L])
		waveLength -= d;
	if (keys[GLFW_KEY_P])
		waveLength += d;
	// fala okres
	if (keys[GLFW_KEY_O])
		wavePeriod -= p;
	if (keys[GLFW_KEY_K])
		wavePeriod += p;


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

Keyboard::~Keyboard()
{
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
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