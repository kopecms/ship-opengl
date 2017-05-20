#pragma once
class Ship
{

	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> ship_coord;

public:
	Ship();
	~Ship();

	void Draw(const glm::mat4&, GLuint modelLoc) const;
};

