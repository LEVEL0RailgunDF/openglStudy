// openglTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>


#include "Angel.h"



static char* readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "rb");
	if (fp == NULL) { return NULL; }
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);
	buf[size] = '\0';
	fclose(fp);

	
	return buf;
}

GLuint InitShader(const char* vShaderFile, const char* fShaderFile) {
	struct Shader {
		const char* filename;
		GLenum type;
		GLchar* source;
	}shaders[2] = { { vShaderFile, GL_VERTEX_SHADER, NULL },{ fShaderFile,GL_FRAGMENT_SHADER, NULL } };
	GLuint program = glCreateProgram();
	
	for (int i = 0; i < 2; ++i) {
		Shader& s = shaders[i];
		s.source = readShaderSource(s.filename);
		if (shaders[i].source == NULL) {
			std::cerr << "Failed to read " << s.filename << std::endl;
			exit(EXIT_FAILURE);
		}
		GLuint shader = glCreateShader(s.type);
		glShaderSource(shader, 1, (const GLchar**)&s.source, NULL);

		glCompileShader(shader);

		

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);



		if (!compiled) {
			std::cerr << s.filename << " failed to compile:" << std::endl;
			GLint logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];

			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;
			exit(EXIT_FAILURE);
		}

		delete[] s.source;
		glAttachShader(program, shader);

	}


	glLinkProgram(program);
	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked) {
		std::cerr << "Shader program failed to link" << std::endl;
		GLint logSize;
		glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logSize);
		char* logMsg = new char[logSize];
		glGetProgramInfoLog(program, logSize, NULL, logMsg);
		std::cerr << logMsg << std::endl;
		delete[] logMsg;
		exit(EXIT_FAILURE);

	}	

	glUseProgram(program);
	return program;

}


const int NumPoints = 100000;

//----------------------------------------------------------------------------

void
init(void)
{
	vec2 points[NumPoints];

	// Specifiy the vertices for a triangle
	vec2 vertices[3] = {
		vec2(-1.0, -1.0), vec2(0.0, 1.0), vec2(1.0, -1.0)
	};

	// Select an arbitrary initial point inside of the triangle
	points[0] = vec2(0.25, 0.50);

	// compute and store N-1 new points
	for (int i = 1; i < NumPoints; ++i) {
		int j = rand() % 3;   // pick a vertex at random

		// Compute the point halfway between the selected vertex
		//   and the previous point
		points[i] = (points[i - 1] + vertices[j]) / 2.0;
	}

	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader21.glsl", "fshader21.glsl");
	glUseProgram(program);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

//----------------------------------------------------------------------------

void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the window
	glDrawArrays(GL_POINTS, 0, NumPoints);    // draw the points
	glFlush();
}

//----------------------------------------------------------------------------

void
keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 033:
		exit(EXIT_SUCCESS);
		break;
	}
}

//----------------------------------------------------------------------------

int
main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);

	// If you are using freeglut, the next two lines will check if 
	// the code is truly 3.2. Otherwise, comment them out

	glutInitContextVersion(3, 2);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Sierpinski Gasket");

	glewExperimental = GL_TRUE;
	glewInit();

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
