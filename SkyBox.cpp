#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SkyBox.h"
using namespace std;

static GLfloat unit_cube[] = {
	-0.5f, -0.5f, -0.5f, 0.25f, 0.66666f,
	0.5f, -0.5f, -0.5f, 0.5f, 0.66666f,
	0.5f, 0.5f, -0.5f, 0.5f, 0.33333f,
	0.5f, 0.5f, -0.5f, 0.5f, 0.33333f,
	-0.5f, 0.5f, -0.5f, 0.25f, 0.33333f,
	-0.5f, -0.5f, -0.5f, 0.25f, 0.66666f,

	-0.5f, -0.5f, 0.5f, 1.0f, 0.66666f,
	0.5f, -0.5f, 0.5f, 0.75f, 0.66666f,
	0.5f, 0.5f, 0.5f, 0.75f, 0.33333f,
	0.5f, 0.5f, 0.5f, 0.75f, 0.33333f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.33333f,
	-0.5f, -0.5f, 0.5f, 1.0f, 0.66666f,

	-0.5f, 0.5f, 0.5f, 0.0f, 0.33333f, 
	-0.5f, 0.5f, -0.5f, 0.25f, 0.33333f,
	-0.5f, -0.5f, -0.5f, 0.25f, 0.66666f,
	-0.5f, -0.5f, -0.5f, 0.25f, 0.66666f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.66666f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.33333f,

	0.5f, 0.5f, 0.5f, 0.75f, 0.33333f,
	0.5f, 0.5f, -0.5f, 0.5f, 0.33333f,
	0.5f, -0.5f, -0.5f, 0.5f, 0.66666f,
	0.5f, -0.5f, -0.5f, 0.5f, 0.66666f,
	0.5f, -0.5f, 0.5f, 0.75f, 0.66666f,
	0.5f, 0.5f, 0.5f, 0.75f, 0.33333f,

	-0.5f, -0.5f, -0.5f, 0.25f, 0.33333f,
	0.5f, -0.5f, -0.5f, 0.5f, 0.33333f,
	0.5f, -0.5f, 0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.25f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.25f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.25f, 0.33333f,

	-0.5f, 0.5f, -0.5f, 0.25f, 0.33333f,
	0.5f, 0.5f, -0.5f, 0.5f, 0.33333f,
	0.5f, 0.5f, 0.5f, 0.5f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.5f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.25f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.25f, 0.33333f,
};

SkyBox::SkyBox(GLfloat size)
{
	for (int i = 0; i < _countof(unit_cube) / 5; ++i)
	{
		cube_coord.push_back(unit_cube[i * 5] * size);
		cube_coord.push_back(unit_cube[i * 5 + 1] * size);
		cube_coord.push_back(unit_cube[i * 5 + 2] * size);
		cube_coord.push_back(unit_cube[i * 5 + 3]);
		cube_coord.push_back(unit_cube[i * 5 + 4]);
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

void SkyBox::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);

	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrans));

	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)cube_coord.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}


SkyBox::~SkyBox()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
static GLfloat unit_cube2[] = {
	-1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,

	-1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	-1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	-1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,

	-1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	-1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,

	-1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	-1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,

	-1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	-1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,

	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,

};