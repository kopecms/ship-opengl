#pragma once
#include <map>
using namespace std;
class Textures {
private:
	static Textures *tm;
	map<string, int> texmap;
	GLuint textures[10];


public:
	Textures();
	~Textures();

	static Textures* getInstance();
	GLuint LoadMipmapTexture(const char* fname);
	void setTexture(string name);

};