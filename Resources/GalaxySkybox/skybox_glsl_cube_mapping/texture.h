#include "buffer.h"

// ----------------------------------------------------------------------------------------------------------------------------

extern int gl_max_texture_size, gl_max_texture_max_anisotropy_ext;

// ----------------------------------------------------------------------------------------------------------------------------

class CTexture
{
private:
	GLuint Texture;

public:
	CTexture();
	~CTexture();

	operator GLuint ();

	bool LoadTexture2D(char *FileName);
	bool LoadTextureCubeMap(char **FileNames);
	void Destroy();

private:
	FIBITMAP *GetBitmap(char *FileName, int &Width, int &Height, int &BPP);
};
