#ifndef _GL_UTILITIES_
#define _GL_UTILITIES_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __APPLE__
	#define GL_SILENCE_DEPRECATION
	#include <OpenGL/gl3.h>
#else
	#if defined(_WIN32)
		#include "glew.h"
		#include <GL/gl.h>
	#else
		#include <GL/gl.h>
	#endif
#endif
#include <stdlib.h>



void printError(const char *functionName);
GLuint loadShaders(const char *vertFileName, const char *fragFileName);
GLuint loadShadersG(const char *vertFileName, const char *fragFileName, const char *geomFileName);
GLuint loadShadersGT(const char *vertFileName, const char *fragFileName, const char *geomFileName,
						const char *tcFileName, const char *teFileName);
void dumpInfo(void);


#ifdef __cplusplus
}
#endif

#endif
