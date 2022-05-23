// demo01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <gl/glew.h>
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h> 


#include <iostream>
#include "../common/common.h"
#include "../common//myMat.h"



//const int NumtimesToSubdivide = 5;
//const int NumTriangles = 729;
//const int NumVertices = 3 * NumTriangles;

const int NumtimesToSubdivide = 1;
const int NumTriangles = 3;
const int NumVertices = 3 * NumTriangles;


vec2 points[NumVertices];
static int VerticesIndex = 0;
void triangle(vec2 a, vec2 b, vec2 c) {
	points[VerticesIndex] = a;
	VerticesIndex++;
	points[VerticesIndex] = b;
	VerticesIndex++;
	points[VerticesIndex] = c;
	VerticesIndex++;

	std::cout << VerticesIndex << std::endl;
}


void divide_triangle(vec2 a, vec2 b, vec2 c,int k) {


	if (k > 0) {
		vec2 ab = (a + b) / 2.0;
		vec2 ac = (a + c) / 2.0;
		vec2 bc = (b + c) / 2.0;

		divide_triangle(a,ab,ac,k-1);
		divide_triangle(ab, b, bc, k - 1);
		divide_triangle(ac, bc, c, k - 1);
	}
	else {
		triangle(a, b, c);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);     // clear the window
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);    // draw the TRIANGLES
	glFlush();
}

void init() {
	vec2 a = vec2(-1.0, -1.0);
	vec2 b = vec2(0.0, 1.0);
	vec2 c = vec2(1.0, -1.0);
	divide_triangle(a, b, c, NumtimesToSubdivide);

	

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
	GLuint program = InitShader("E:/opengl/openglStudy/demo01/vshader21.glsl", "E:/opengl/openglStudy/demo01/fshader21.glsl");
	glUseProgram(program);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background


}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640, 480);//显示窗口的大小
	//glutInitWindowPosition(0, 0);//显示窗口的位置

	//glutInitContextVersion(3, 2);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Sierpinski Gasket");

	glewExperimental = GL_TRUE;
	glewInit();


	init();


	glutDisplayFunc(display);



	glutMainLoop();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
