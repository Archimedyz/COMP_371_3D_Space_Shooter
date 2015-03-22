#include "LoadBMP.h"

typedef struct Bitmap {
	int offset;
	int width;
	int height;
	int bpp;
	int encoding;
	int size;
	bool loaded;
	unsigned char* pData;
};