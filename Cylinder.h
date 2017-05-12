#pragma once
class Cylinder
{
	GLuint VAO;
	GLuint VBO;
	std::vector<GLfloat> cylinder_coord;


public:
	Cylinder();
	Cylinder(float radius_1, float radius_2, float heigth, int triangles);
	void set(float radius_1, float radius_2, float heigth, int triangles);
	~Cylinder();
	void Draw(const glm::mat4&, GLuint modelLoc) const;

};

