
#define GLEW_STATIC
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>
#include <map>
#include "Textures.h"
using namespace std;

Textures* Textures::tm = nullptr;

GLuint Textures::LoadMipmapTexture(const char* fname)
{
	int width, height;
	unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
	if (image == nullptr)
		throw exception("Failed to load texture file");

	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

void Textures::setTexture(string name)
{
	glBindTexture(GL_TEXTURE_2D, texmap[name]);
	//glUniform1i(glGetUniformLocation(programId, "Texture0"), 0);

}

Textures::Textures()
{
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures

	textures[0] = LoadMipmapTexture("weiti.png");
	textures[1] = LoadMipmapTexture("skybox.jpg");
	textures[2] = LoadMipmapTexture("water.jpg");
	texmap["weiti"] = textures[0];
	texmap["skybox"] = textures[1];
	texmap["water"] = textures[2];
}

Textures* Textures::getInstance()
{
	if (!tm)
		tm = new Textures();
	return tm;
}

Textures::~Textures()
{
	if (tm)
		delete tm;
}
