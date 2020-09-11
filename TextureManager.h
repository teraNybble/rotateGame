#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#pragma warning(disable : 4996)//couldn't give a toss that fopen is unsafe

#include "glew.h"
#include <map>
#include <string>
#include <Rect.h>
#include <png.h>

class TextureManager
{
private:
	//should be std::map
	static std::map<int, GLuint> textures;
	static bool loadPNGFromFile(const char* name, Game2D::Rect& rect, bool& outHasAlpha, GLubyte** outData);
	static GLuint loadPNG(const char* path);
public:
	static void loadTextures(std::string path, int identifier, int filter = GL_LINEAR);
	static GLuint getTexture(int identifier);
};

#endif // !TEXTUREMANAGER_H