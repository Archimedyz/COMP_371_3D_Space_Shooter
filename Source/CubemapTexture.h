//From http://ogldev.atspace.co.uk/www/tutorial25/tutorial25.html


//also http://www.learnopengl.com/#!Advanced-OpenGL/Cubemaps

//and
#include <GLFW/glfw3.h>
#include <string.h>
#include <stringapiset.h>

class CubemapTexture
{
public:
	CubemapTexture(const string& Directory,
		const string& PosXFilename,
		const string& NegXFilename,
		const string& PosYFilename,
		const string& NegYFilename,
		const string& PosZFilename,
		const string& NegZFilename);

	~CubemapTexture();

	bool Load();

	void Bind(GLenum TextureUnit);

private:

	string m_fileNames[6];
	GLuint m_textureObj;
};