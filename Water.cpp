#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Water.h"
#include <iostream>
using namespace std;

Water::Water(GLfloat size, int triangles)
{
	int bok = (int) sqrt( triangles / 2);
	
	for (int i = -bok; i < bok ; ++i)
	{
		for (int j = -bok; j < bok; j++)
		{
			cube_coord.push_back(i/(GLfloat)bok * size);
			cube_coord.push_back(0.0);
			cube_coord.push_back(j / (GLfloat)bok * size);
			cube_coord.push_back(0.0f);
			cube_coord.push_back(0.0f);

			cube_coord.push_back((i + 1) / (GLfloat)bok * size);
			cube_coord.push_back(0.0);
			cube_coord.push_back(j / (GLfloat)bok * size);
			cube_coord.push_back(1.0f);
			cube_coord.push_back(0.0f);

			cube_coord.push_back(i / (GLfloat)bok * size);
			cube_coord.push_back(0.0);
			cube_coord.push_back((j + 1) / (GLfloat)bok * size);
			cube_coord.push_back(0.0f);
			cube_coord.push_back(1.0f);
			
			cube_coord.push_back((i) / (GLfloat)bok * size);
			cube_coord.push_back(0.0);
			cube_coord.push_back((j + 1) / (GLfloat)bok * size);
			cube_coord.push_back(0.0f);
			cube_coord.push_back(1.0f);

			cube_coord.push_back((i + 1) / (GLfloat)bok * size);
			cube_coord.push_back(0.0);
			cube_coord.push_back((j + 1) / (GLfloat)bok * size);
			cube_coord.push_back(1.0f);
			cube_coord.push_back(1.0f);

			cube_coord.push_back((i + 1) / (GLfloat)bok * size);
			cube_coord.push_back(0.0);
			cube_coord.push_back(j / (GLfloat)bok * size);
			cube_coord.push_back(1.0f);
			cube_coord.push_back(0.0f);
		}
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * cube_coord.size(), &(cube_coord[0]), GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Water::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);
	glm::mat4& model = glm::translate(modelTrans, glm::vec3(0, -8, 0));
	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)cube_coord.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}

Water::~Water()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
