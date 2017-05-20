#define GLEW_STATIC
#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Ship.h"
#include <iostream>
using namespace std;

GLfloat p[4][2] { { 0.5, -1 }, 
				{ 0.5, 0.25},
				{0.75/2, 1.75/2},
				{0, 1}};

GLfloat bezier_point_x(GLfloat t){
	return ((1 - t)*((1 - t)*((1 - t)*p[0][0] + t*p[1][0]) + t*((1 - t)*p[1][0] + t*p[2][0]))
		+ t*((1 - t)*((1 - t)*p[1][0] + t*p[2][0]) + t*((1 - t)*p[2][0] + t*p[3][0])));
}

GLfloat bezier_point_y(GLfloat t){
	return (1 - t)*((1 - t)*((1 - t)*p[0][1] + t*p[1][1]) + t*((1 - t)*p[1][1] + t*p[2][1])) 
		+ t*((1 - t)*((1 - t)*p[1][1] + t*p[2][1]) + t*((1 - t)*p[2][1] + t*p[3][1]));
}

GLfloat q = 10.0;
GLfloat t(int i){
	return i /q ;
}
Ship::Ship()
{
	int size= 2;
	
	for (int i = 0; i < 10; i++){
		//1
		ship_coord.push_back(bezier_point_x(t(i))*size);
		ship_coord.push_back(0.0*size);
		ship_coord.push_back(bezier_point_y(t(i))*size);
		ship_coord.push_back(bezier_point_x(t(i))*size);
		ship_coord.push_back(bezier_point_y(t(i))*size);

		ship_coord.push_back(-bezier_point_x(t(i))*size);
		ship_coord.push_back(0.0*size);
		ship_coord.push_back(bezier_point_y(t(i))*size);
		ship_coord.push_back(-bezier_point_x(t(i))*size);
		ship_coord.push_back(bezier_point_y(t(i))*size);

		ship_coord.push_back(-bezier_point_x(t(i+1))*size);
		ship_coord.push_back(0.0*size);
		ship_coord.push_back(bezier_point_y(t(i+1))*size);
		ship_coord.push_back(-bezier_point_x(t(i+1))*size);
		ship_coord.push_back(bezier_point_y(t(i+1))*size);
		//2
		ship_coord.push_back(-bezier_point_x(t(i + 1))*size);
		ship_coord.push_back(0.0*size);
		ship_coord.push_back(bezier_point_y(t(i + 1))*size);
		ship_coord.push_back(-bezier_point_x(t(i + 1))*size);
		ship_coord.push_back(bezier_point_y(t(i + 1))*size);

		ship_coord.push_back(bezier_point_x(t(i + 1))*size);
		ship_coord.push_back(0.0*size);
		ship_coord.push_back(bezier_point_y(t(i + 1))*size);
		ship_coord.push_back(bezier_point_x(t(i + 1))*size);
		ship_coord.push_back(bezier_point_y(t(i + 1))*size);

		ship_coord.push_back(bezier_point_x(t(i))*size);
		ship_coord.push_back(0.0*size);
		ship_coord.push_back(bezier_point_y(t(i))*size);
		ship_coord.push_back(bezier_point_x(t(i))*size);
		ship_coord.push_back(bezier_point_y(t(i))*size);
	}
	float n =3;
	int m = 10;
	float height = 1;
	float d = 5;
	auto gl = [](int a, float b) { return ((a*a) / b)+1; };
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < m ; ++j){
			// 1
			ship_coord.push_back(bezier_point_x(t(j))*size/gl(i,d));
			ship_coord.push_back(-i/n*height);
			ship_coord.push_back(bezier_point_y(t(j))*size);
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(1.0*size);

			ship_coord.push_back(bezier_point_x(t(j + 1))*size/ gl(i,d));
			ship_coord.push_back(-i / n*height);
			ship_coord.push_back(bezier_point_y(t(j + 1))*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(1.0*size);


			ship_coord.push_back(bezier_point_x(t(j))*size/ gl(i+1, d));
			ship_coord.push_back(-(i +1)/ n*height);
			ship_coord.push_back(bezier_point_y(t(j))*size);
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(0.0*size);
			// 2
			ship_coord.push_back(bezier_point_x(t(j))*size/ gl(i+1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(bezier_point_y(t(j))*size );
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(bezier_point_x(t(j+1))*size/ gl(i+1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(bezier_point_y(t(j + 1))*size );
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(bezier_point_x(t(j + 1))*size/ gl(i, d));
			ship_coord.push_back(-i / n*height);
			ship_coord.push_back(bezier_point_y(t(j + 1))*size );
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(1.0*size);

			// 1 druga strona
			ship_coord.push_back(-bezier_point_x(t(j))*size / gl(i, d));
			ship_coord.push_back(-i / n*height);
			ship_coord.push_back(bezier_point_y(t(j))*size);
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(1.0*size);

			ship_coord.push_back(-bezier_point_x(t(j + 1))*size / gl(i, d));
			ship_coord.push_back(-i / n*height);
			ship_coord.push_back(bezier_point_y(t(j + 1))*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(1.0*size);


			ship_coord.push_back(-bezier_point_x(t(j))*size / gl(i + 1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(bezier_point_y(t(j))*size);
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(0.0*size);
			// 2
			ship_coord.push_back(-bezier_point_x(t(j))*size / gl(i + 1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(bezier_point_y(t(j))*size);
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(-bezier_point_x(t(j + 1))*size / gl(i + 1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(bezier_point_y(t(j + 1))*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(-bezier_point_x(t(j + 1))*size / gl(i, d));
			ship_coord.push_back(-i / n*height);
			ship_coord.push_back(bezier_point_y(t(j + 1))*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(1.0*size);

			//tyl
			ship_coord.push_back(-0.5*size / gl(i + 1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(-1.0*size);
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(0.5*size / gl(i + 1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(-1.0*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(-0.5*size / gl(i, d));
			ship_coord.push_back(-i / n*height);
			ship_coord.push_back(-1.0*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(1.0*size);
			// drugi trojkat
			ship_coord.push_back(0.5*size / gl(i + 1, d));
			ship_coord.push_back(-(i + 1) / n*height);
			ship_coord.push_back(-1.0*size);
			ship_coord.push_back(0.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(0.5*size / gl(i, d));
			ship_coord.push_back(-(i) / n*height);
			ship_coord.push_back(-1.0*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(0.0*size);


			ship_coord.push_back(-0.5*size / gl(i, d));
			ship_coord.push_back(-(i) / n*height);
			ship_coord.push_back(-1.0*size);
			ship_coord.push_back(1.0*size);
			ship_coord.push_back(1.0*size);

		}
	}



	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * ship_coord.size(), &(ship_coord[0]), GL_STATIC_DRAW);

	// vertex geometry data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// vertex texture coordinates
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void Ship::Draw(const glm::mat4& modelTrans, GLuint modelLoc) const
{
	glBindVertexArray(VAO);
	glm::mat4& model = glm::translate(modelTrans, glm::vec3(0, 0, 0));
	// no internal transformations for now
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, (GLuint)ship_coord.size());

	// all is drawn - unbind vertex array
	glBindVertexArray(0);
}

Ship::~Ship()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
