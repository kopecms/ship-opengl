#pragma once
class Water
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> cube_coord;

public:
	Water(GLfloat size, int triangles);
	~Water();
	void Draw(const glm::mat4&, GLuint modelLoc) const;
};

