#pragma once
class Circle
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> circle_coord;
public:
	Circle(float radius_1, float radius_2, float d, float heigth, int triangles);
	~Circle();

	void Draw(const glm::mat4&, GLuint modelLoc) const;
};

