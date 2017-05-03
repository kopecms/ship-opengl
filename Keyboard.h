#pragma once

extern bool keys[1024];

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

class Keyboard
{
private:
	float d = 0.01;
	float p = 0.001;
public:
	

	bool isWater = false;
	float waveLength = 10;
	float wavePeriod = 4;

	float xRotation = 0.0f;

	//Camera
	GLfloat pitch = 0.0f; // elewacja
	const GLfloat pitch_max = 80.0f, pitch_min = -80.0f;

	GLfloat yaw = 0.0f; // azymut
	const GLfloat yaw_max = 360.0f, yaw_min = 0.0f;


	Keyboard();
	void doMovement(GLfloat deltaTime);
	~Keyboard();
};

 
	