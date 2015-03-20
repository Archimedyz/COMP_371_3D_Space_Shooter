// ----------------------------------------------------------------------------------------------------------------------------
//
// Version 1.09b
//
// ----------------------------------------------------------------------------------------------------------------------------

#include <windows.h>

#include "glmath.h"
#include "string.h"

#include <gl/glew.h> // http://glew.sourceforge.net/
#include <gl/wglew.h>

#include <FreeImage.h> // http://freeimage.sourceforge.net/

// ----------------------------------------------------------------------------------------------------------------------------

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "FreeImage.lib")

// ----------------------------------------------------------------------------------------------------------------------------

extern CString ModuleDirectory, ErrorLog;
