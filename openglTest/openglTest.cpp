// openglTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <windows.h> 

#include <gl/glew.h>
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h> 

#include "myMat.h"

#include <cstdlib>  
#include <cstdio>  
#include <cmath> 




//通过鼠标来控制矩形的移动
int xd = 0, yd = 0;

//绘制一个矩形
void display(void) {
	glClear(GL_COLOR_BUFFER_BIT);//用颜色刷新
	glColor3f(0.8, 0.5, 0.6);//绘制的颜色
	glPointSize(5);//绘制像素的大小
	glBegin(GL_POLYGON);
	glVertex2i(10 + xd, 10 + yd);//第一点
	glVertex2i(20 + xd, 10 + yd);//第二点
	glVertex2i(20 + xd, 0 + yd);
	glVertex2i(10 + xd, 0 + yd);
	glEnd();
	glFlush();
}

//键盘点击函数
void myKayBoard(unsigned char key, int x, int y) {//key对应键盘上面的一个键
	switch (key)
	{
	case'w':yd++; break;//在键盘上面按w键的话。yd值加一
	case's':yd--; break;//在键盘上面按w键的话。yd值减一
	case'a':xd++; break;//在键盘上面按w键的话。yx值加一
	case'd':xd--; break;//在键盘上面按w键的话。yx值jian一
	}
	//改变值后我们要使图形重新显示一遍
	glutPostRedisplay();

}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 1.1);//申明一个刷新的颜色
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-20.0, 30.0, -20.0, 30.0);
	//glShadeModel(GL_FLAT);
}


//int main(int argc, char** argv) {
//	glutInit(&argc, argv);//初始化openGl
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//	glutInitWindowPosition(100, 100);//显示窗口的位置
//	glutInitWindowSize(350, 150);//显示窗口的大小
//	glutCreateWindow("kry interaction");//表示用键盘来进行交互的
//
//	init();//自定义的方法
//	glutDisplayFunc(display);//绘制函数
//	glutKeyboardFunc(myKayBoard);//点击键盘的时候就会调用该方法
//	glutMainLoop();
//	return 0;
//}

//绘制
void display1(void) {
	glClear(GL_COLOR_BUFFER_BIT);//用颜色刷新
	glDrawArrays(GL_POINTS,0,500);
	glFlush();
}

void triangle(vec2 a, vec2 b, vec2 c)
{
	//static int i = 0;
	//points[i] = a;
	//i++;
	//points[i] = b;
	//i++;
	//points[i] = c;
	//i++;
}

static char* readShaderSource(const char* shaderFile)
{
	FILE* fp = fopen(shaderFile, "r");
	if (fp == NULL) { return NULL; }
	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, fp);
	buf[size] = ' ';
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
			std::cerr << "Failed to read" << s.filename << std::endl;
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
			glGetShaderInfoLog(program, logSize, NULL, logMsg);
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




int main(int argc, char** argv) {
	const int pointNumber = 5000;
	vec2 points[pointNumber];

	vec2 vertices[3] = { vec2(-1.0,-1.0),vec2(0.0,1.0),vec2(1.0,0.0) };
	
	points[0] = vec2(0.25, 0.5);
	//printf("%lf,%lf\n", points[0].x, points[0].y);

	for (int k = 1; k < pointNumber; k++)
	{
		int j= rand()%3;
		points[k] = (points[k - 1] + vertices[j] / 2.0);
		//printf("%lf,%lf\n", points[k].x, points[k].y);
	}

	glutInit(&argc,argv);

	glutCreateWindow("opengl");
	glutInitDisplayMode( GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(640, 480);//显示窗口的大小
	glutInitWindowPosition(0, 0);//显示窗口的位置
	glewInit();
	glutDisplayFunc(display1);

	init();


	GLuint abuffer;
	glGenVertexArrays(1, &abuffer);
	glBindVertexArray(abuffer);

	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points),points,GL_STATIC_DRAW);

	GLuint program;
	program = InitShader("vsource,glsl", "fsource.glsl");


	glutMainLoop();

	
}


