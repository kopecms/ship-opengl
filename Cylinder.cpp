#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Cylinder.h"

#include <iostream>
using namespace std;
#define PI 3.14
Cylinder::Cylinder(float radius_1,float radius_2,float heigth, int triangles)
{
	for (int i = 0; i < triangles / 4; ++i)
	{
		// gora
		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_1);

		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);

		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);

		// sciana

		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(-1.0f);
		cylinder_coord.push_back(1.0f*heigth);


		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(1.0f);
		cylinder_coord.push_back(1.0f*heigth);


		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(-1.0f);
		cylinder_coord.push_back(-1.0f*heigth);

		// sciana 2

		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(1.0f);
		cylinder_coord.push_back(1.0f*heigth);

		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(-1.0f*heigth);


		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(-1.0f*heigth);
		// dol

		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);

		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);

		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_2);

	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cylinder_coord.size(), &(cylinder_coord[0]), GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
Cylinder::Cylinder()
{}
void Cylinder::set(float radius_1, float radius_2, float heigth, int triangles)
{
	for (int i = 0; i < triangles / 4; ++i)
	{
		// gora
		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_1);

		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);

		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);

		// sciana

		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(-1.0f);
		cylinder_coord.push_back(1.0f*heigth);


		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(1.0f);
		cylinder_coord.push_back(1.0f*heigth);


		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(-1.0f);
		cylinder_coord.push_back(-1.0f*heigth);

		// sciana 2

		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_1);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(1.0f);
		cylinder_coord.push_back(1.0f*heigth);

		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(-1.0f*heigth);


		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(1.0f*heigth);
		cylinder_coord.push_back(-1.0f*heigth);
		// dol

		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(cos(i*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin(i*4.0 / triangles * 2 * PI)*radius_2);

		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(0.0f);
		cylinder_coord.push_back(0.0f);

		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(-1.0f*heigth);
		cylinder_coord.push_back(cos((i + 1)*4.0 / triangles * 2 * PI)*radius_2);
		cylinder_coord.push_back(sin((i + 1)*4.0 / triangles * 2 * PI)*radius_2);

	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cylinder_coord.size(), &(cylinder_coord[0]), GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void Cylinder::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);
	glm::mat4& model = glm::translate(modelTrans, glm::vec3(0, 0, 0));
	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)cylinder_coord.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}


Cylinder::~Cylinder()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
