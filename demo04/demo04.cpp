// demo01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <gl/glew.h>
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h> 


#include <iostream>
#include "../common/common.h"
#include "../common//myMat.h"
#include "../common//myMat.cpp" 


vec4 vertices[8] = {
	vec4(-0.5, -0.5, 0.5, 1.0) ,vec4(-0.5, 0.5, 0.5, 1.0),
	vec4(0.5, 0.5, 0.5, 1.0), vec4(0.5, -0.5, 0.5, 1.0),
	vec4(-0.5,-0.5, -0.5, 1.0), vec4(-0.5,0.5, -0.5, 1.0),
	vec4(0.5,0.5,-0.5,1.0), vec4(0.5,-0.5 ,-0.5,1.0)


};

vec4 colors[8] = {
	vec4(0.0, 0.0, 0.0, 1.0),
	vec4(1.0, 0.0, 0.0, 1.0),
	vec4(1.0, 1.0, 0.0, 1.0),
	vec4(0.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0),
	vec4(1.0, 0.0, 1.0, 1.0),
	vec4(0.0, 1.0, 1.0, 1.0),
	vec4(1.0, 1.0, 1.0, 1.0),

};

vec4 points[36];
vec4 quad_colors[36];

enum {
	Xaxis = 0,
	Yaxis = 1,
	Zaxis = 2,
	NumAxes = 3
};

int Axis = Xaxis;
GLfloat TheTa[NumAxes] = { 0.0, 0.0 , 0.0 };
GLint matrix_loc;




int i = 0;
void quad(int a, int b, int c, int d) {
	quad_colors[i] = colors[a];
	points[i] = vertices[a];
	i++;

	quad_colors[i] = colors[b];
	points[i] = vertices[b];
	i++;

	quad_colors[i] = colors[c];
	points[i] = vertices[c];
	i++;



	quad_colors[i] = colors[a];
	points[i] = vertices[a];
	i++;

	quad_colors[i] = colors[c];
	points[i] = vertices[c];
	i++;

	quad_colors[i] = colors[d];
	points[i] = vertices[d];
	i++;




}

void spinCube() {
	TheTa[Axis] += 0.01;
	if (TheTa[Axis] > 360.0) {
		TheTa[Axis] = -360.0;
	}
	glutPostRedisplay();
}

void myMouse(int button, int state, int x, int y) {

		if (button == GLUT_LEFT_BUTTON)
		{
			Axis = 0;
			std::cout << "0";
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			Axis = 1;
			std::cout << "1";

		}
		else if (button == GLUT_MIDDLE_BUTTON) {
			Axis = 2;
			std::cout << "2";
		}


	return;
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window
	mat4 ctm = RotateX(TheTa[0]) * RotateY(TheTa[1]) * RotateZ(TheTa[2]);
	glUniformMatrix4fv(matrix_loc,1,GL_TRUE, static_cast<GLfloat*>(&ctm._m[0].x));
	glDrawArrays(GL_TRIANGLES, 0, 36);    // draw the TRIANGLES
	glFlush();
}

void init() {

	quad(0, 3, 2, 1);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);
	quad(1, 2, 6, 5);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);



	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(quad_colors), NULL, GL_STATIC_DRAW);


	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(quad_colors), quad_colors);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("../../vshader04.glsl", "../../fshader04.glsl");
	glUseProgram(program);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));


	GLuint loc2 = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points)));


	matrix_loc = glGetUniformLocation(program, "rotation");

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background


}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(640, 480);//显示窗口的大小
	//glutInitWindowPosition(0, 0);//显示窗口的位置

	//glutInitContextVersion(3, 2);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("color cube");

	glewExperimental = GL_TRUE;
	glewInit();


	init();

	glutIdleFunc(spinCube);
	glutMouseFunc(myMouse);

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
