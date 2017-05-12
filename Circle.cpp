
#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Circle.h"
using namespace std;
#define PI 3.14

Circle::Circle(float radius_1, float radius_2, float d,float heigth, int triangles)
{

	for (int i = 0; i < triangles / 8; ++i)
	{
		// gora
		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*radius_1);

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);

		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);

		// gora 2

		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*d);

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);

		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);

		// sciana

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(-1.0f);
		circle_coord.push_back(1.0f*heigth);


		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(1.0f);
		circle_coord.push_back(1.0f*heigth);


		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(-1.0f);
		circle_coord.push_back(-1.0f*heigth);

		// sciana 2

		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(1.0f);
		circle_coord.push_back(1.0f*heigth);

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(-1.0f*heigth);


		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(-1.0f*heigth);
		
		// sciana d

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(-1.0f);
		circle_coord.push_back(1.0f*heigth);


		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(1.0f);
		circle_coord.push_back(1.0f*heigth);


		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(-1.0f);
		circle_coord.push_back(-1.0f*heigth);

		// sciana 2

		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(1.0f);
		circle_coord.push_back(1.0f*heigth);

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(-1.0f*heigth);


		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(1.0f*heigth);
		circle_coord.push_back(-1.0f*heigth);
		
		// dol

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*radius_2);


		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);

		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_2);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_2);
		//dol 2


		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*d);

		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(cos(i*8.0 / triangles * 2 * PI)*d);
		circle_coord.push_back(sin(i*8.0 / triangles * 2 * PI)*d);

		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(-1.0f*heigth);
		circle_coord.push_back(cos((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
		circle_coord.push_back(sin((i + 1)*8.0 / triangles * 2 * PI)*radius_1);
	}
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * circle_coord.size(), &(circle_coord[0]), GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void Circle::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);
	glm::mat4& model = glm::translate(modelTrans, glm::vec3(0, 0, 0));
	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)circle_coord.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}

Circle::~Circle()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
