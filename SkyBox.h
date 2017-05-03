#pragma once
class SkyBox
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> cube_coord;

	std::vector<GLfloat> vertices;
	std::vector<GLuint> indices;

public:
	SkyBox(GLfloat size);
	~SkyBox();
	void Draw(const glm::mat4&, GLuint modelLoc) const;
};
