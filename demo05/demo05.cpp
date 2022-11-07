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


GLfloat radius = 1.0;
GLfloat theta = 0.0;
GLfloat phi = 0.0;

const GLfloat dr = 5.0 * DegreesToRadians;

GLuint model_view;

GLfloat left = -1.0, right = 1.0;
GLfloat bottom = -1.0, top = 1.0;
GLfloat zNear = -1.0, zFar = 1.0;

GLfloat projection;


enum {
	Xaxis = 0,
	Yaxis = 1,
	Zaxis = 2,
	NumAxes = 3
};

int Axis = Xaxis;
GLfloat TheTa[NumAxes] = { 0.0, 0.0 , 0.0 };


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



void keyboard(unsigned char key, int x,int y) {
	std::cout << key;
	switch (key)
	{
		case 033:
		case 'q': case 'Q':
			exit(EXIT_SUCCESS);
			break;
		case 'x': left *= 1.1; right *= 1.1; break;
		case 'X': left *= 0.9; right *= 0.9; break;
		case 'y': bottom *= 1.1; top *= 1.1; break;
		case 'Y': bottom *= 0.9; top *= 0.9; break;
		case 'z': zNear *= 1.1; zFar *= 1.1; break;
		case 'Z': zNear *= 0.9; zFar *= 0.9; break;
		case 'r': radius *= 2.0; break;
		case 'R': radius *= 0.5; break;
		case 'o': theta += dr; break;
		case 'O': theta -= dr; break;
		case 'p': phi += dr; break;
		case 'P': phi -= dr; break;

		case ' ':  // reset values to their defaults
			left = -1.0;
			right = 1.0;
			bottom = -1.0;
			top = 1.0;
			zNear = 0.5;
			zFar = 3.0;

			radius = 1.0;
			theta = 0.0;
			phi = 0.0;
			break;

	default:
		break;
	}


	return;
}


void display() {
	std::cout << "11111111111";
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window
	vec4 eye(radius * sin(theta) * cos(phi),
		radius * sin(theta) * sin(phi),
		radius * cos(theta),
		1.0);

	vec4 at(0.0,0.0,0.0,1.0);
	vec4 up(0.0, 1.0, 0.0, 0.0);

	mat4 mv = LookAt(eye, at,up);
	glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);

	mat4 p = Frustum(left, right, bottom, top, zNear, zFar);
	glUniformMatrix4fv(projection, 1, GL_TRUE, p);


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
	GLuint program = InitShader("../../vshader05.glsl", "../../fshader05.glsl");
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


	model_view = glGetUniformLocation(program, "model_view");
	projection = glGetUniformLocation(program, "projection");

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

	glutKeyboardFunc(keyboard);

	glutDisplayFunc(display);
	glutIdleFunc(display);

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
