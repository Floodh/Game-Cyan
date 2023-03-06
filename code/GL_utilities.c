// GL utilities, bare essentials
// By Ingemar Ragnemalm

// August 2012:
// FBO creation/usage routines.
// Geometry shader support synched with preliminary version.
// September 2012: Improved infolog printouts with file names.
// 120910: Clarified error messages from shader loader.
// 120913: Re-activated automatic framebuffer checks for UseFBO().
// Fixed FUBAR in InitFBO().
// 130228: Changed most printf's to stderr.
// 131014: Added tesselation shader support
// 150812: Added a NULL check on file names in readFile, makes Visual Studio happier.
// 160302: Uses fopen_s on Windows, as suggested by Jesper Post. Should reduce warnings a bit.
// 200405: Added a few typecasts that were missing.
// 210219: Shader errors are now visible on new VS19.
// 210324: Compiling without fragment shader is now allowed

//#define GL3_PROTOTYPES
#ifdef WIN32
#include <Windows.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "GL_utilities.h"

// Shader loader

char* readFile(char *file)
{
	FILE *fptr;
	long length;
	char *buf;

	if (file == NULL)
			return NULL;

	// It seems Windows/VS doesn't like fopen any more, but fopen_s is not on the others.
	#if defined(_WIN32)
		fopen_s(&fptr, file, "r");
	#else
		fptr = fopen(file, "rb"); // rw works everywhere except Windows?
	#endif
//	fptr = fopen(file, "rb"); /* Open file for reading */
	if (!fptr) /* Return NULL on failure */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	length = ftell(fptr); /* Find out how many bytes into the file we are */
	buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
	memset(buf, 0, sizeof(char)*(length + 1)); /* Clean the buffer - suggested for safety by Mateusz 2016 */
	fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	fclose(fptr); /* Close the file */
	buf[length] = 0; /* Null terminator */

	return buf; /* Return the buffer */
}

// Infolog: Show result of shader compilation
void printShaderInfoLog(GLuint obj, const char *fn)
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 2)
	{
		fprintf(stderr, "[From %s:]\n", fn);
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		fprintf(stderr, "[From %s:]\n", infoLog);
		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj, const char *vfn, const char *ffn,
					const char *gfn, const char *tcfn, const char *tefn)
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;
	char msg[2048] = "\n";

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 2)
	{
		if (ffn == NULL)
			sprintf(msg, "[From %s:]\n", vfn);
		else
		if (gfn == NULL)
			sprintf(msg, "[From %s+%s:]\n", vfn, ffn);
		else
		if (tcfn == NULL || tefn == NULL)
			sprintf(msg, "[From %s+%s+%s:]\n", vfn, ffn, gfn);
		else
			sprintf(msg, "[From %s+%s+%s+%s+%s:]\n", vfn, ffn, gfn, tcfn, tefn);
		if (strlen(msg) > 1)

		fputs(msg, stderr);
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		fputs(infoLog, stderr);
		fputs("\n", stderr);
		free(infoLog);
	}
}

// Compile a shader, return reference to it
GLuint compileShaders(const char *vs, const char *fs, const char *gs, const char *tcs, const char *tes,
								const char *vfn, const char *ffn, const char *gfn, const char *tcfn, const char *tefn)
{
	GLuint v,f,g,tc,te,p;

	v = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v, 1, &vs, NULL);
	glCompileShader(v);
	if (fs != NULL)
	{
		f = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(f, 1, &fs, NULL);
		glCompileShader(f);
	}
	if (gs != NULL)
	{
		g = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(g, 1, &gs, NULL);
		glCompileShader(g);
	}
#ifdef GL_TESS_CONTROL_SHADER
	if (tcs != NULL)
	{
		tc = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(tc, 1, &tcs, NULL);
		glCompileShader(tc);
	}
	if (tes != NULL)
	{
		te = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(te, 1, &tes, NULL);
		glCompileShader(te);
	}
#endif
	p = glCreateProgram();
	if (vs != NULL)
		glAttachShader(p,v);
	if (fs != NULL)
		glAttachShader(p,f);
	if (gs != NULL)
		glAttachShader(p,g);
	if (tcs != NULL)
		glAttachShader(p,tc);
	if (tes != NULL)
		glAttachShader(p,te);
	glLinkProgram(p);
	glUseProgram(p);

	if (vs != NULL) printShaderInfoLog(v, vfn);
	if (fs != NULL) printShaderInfoLog(f, ffn);
	if (gs != NULL)	printShaderInfoLog(g, gfn);
	if (tcs != NULL) printShaderInfoLog(tc, tcfn);
	if (tes != NULL) printShaderInfoLog(te, tefn);

	printProgramInfoLog(p, vfn, ffn, gfn, tcfn, tefn);

	return p;
}

GLuint loadShaders(const char *vertFileName, const char *fragFileName)
{
	return loadShadersGT(vertFileName, fragFileName, NULL, NULL, NULL);
}

GLuint loadShadersG(const char *vertFileName, const char *fragFileName, const char *geomFileName)
// With geometry shader support
{
	return loadShadersGT(vertFileName, fragFileName, geomFileName, NULL, NULL);
}

GLuint loadShadersGT(const char *vertFileName, const char *fragFileName, const char *geomFileName,
						const char *tcFileName, const char *teFileName)
// With tesselation shader support
{
	char *vs, *fs, *gs, *tcs, *tes;
	GLuint p = 0;

	vs = readFile((char *)vertFileName);
	fs = readFile((char *)fragFileName);
	gs = readFile((char *)geomFileName);
	tcs = readFile((char *)tcFileName);
	tes = readFile((char *)teFileName);
	if (vs==NULL)
		fprintf(stderr, "Failed to read %s from disk.\n", vertFileName);
	if (fs==NULL && (fragFileName != NULL))
		fprintf(stderr, "Failed to read %s from disk.\n", fragFileName);
	if ((gs==NULL) && (geomFileName != NULL))
		fprintf(stderr, "Failed to read %s from disk.\n", geomFileName);
	if ((tcs==NULL) && (tcFileName != NULL))
		fprintf(stderr, "Failed to read %s from disk.\n", tcFileName);
	if ((tes==NULL) && (teFileName != NULL))
		fprintf(stderr, "Failed to read %s from disk.\n", teFileName);
	if ((vs!=NULL)&&(fs!=NULL))
		p = compileShaders(vs, fs, gs, tcs, tes, vertFileName, fragFileName, geomFileName, tcFileName, teFileName);
	if (vs != NULL) free(vs);
	if (fs != NULL) free(fs);
	if (gs != NULL) free(gs);
	if (tcs != NULL) free(tcs);
	if (tes != NULL) free(tes);
	return p;
}

// End of Shader loader

void dumpInfo(void)
{
   printf ("Vendor: %s\n", glGetString (GL_VENDOR));
   printf ("Renderer: %s\n", glGetString (GL_RENDERER));
   printf ("Version: %s\n", glGetString (GL_VERSION));
   printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
   printError ("dumpInfo");
}

static GLenum lastError = 0;
static char lastErrorFunction[1024] = "";

/* report GL errors, if any, to stderr */
void printError(const char *functionName)
{
   GLenum error;
   while (( error = glGetError() ) != GL_NO_ERROR)
   {
       if ((lastError != error) || (strcmp(functionName, lastErrorFunction)))
       {
	       fprintf (stderr, "GL error 0x%X detected in %s\n", error, functionName);
	       strcpy(lastErrorFunction, functionName);
	       lastError = error;
       }
   }
}

