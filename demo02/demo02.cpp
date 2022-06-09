// demo01.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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

const int NumtimesToSubdivide = 5;
const int NumTriangles = 4*4*4*4*4*4;
const int NumVertices = 4 * NumTriangles;

vec3 base_color[4] = {
	vec3(1.0, 0.0 , 0.0),
	vec3(0.0, 1.0 , 0.0),
	vec3(0.0, 0.0 , 1.0),
	vec3(0.0, 0.0 , 0.0),
};

vec3 points[NumVertices];
vec3 colors[NumVertices];
static int VerticesIndex = 0;
int colorIndex;


void triangle(vec3 a, vec3 b, vec3 c) {
	points[VerticesIndex] = a;
	colors[VerticesIndex] = base_color[colorIndex];
	VerticesIndex++;
	points[VerticesIndex] = b;
	colors[VerticesIndex] = base_color[colorIndex];
	VerticesIndex++;
	points[VerticesIndex] = c;
	colors[VerticesIndex] = base_color[colorIndex];
	VerticesIndex++;
 
}



void tetra(vec3 a, vec3 b, vec3 c ,vec3 d) {
	colorIndex = 0;
	triangle(a, b, c);

	colorIndex = 1;
	triangle(a, b, d);

	colorIndex = 2;
	triangle(a, c, d);

	colorIndex = 3;
	triangle(b, c, d);
}

void divide_tetra(vec3 a, vec3 b, vec3 c,vec3 d, int k) {


	if (k > 0) {
		vec3 ab = (a + b) / 2.0;
		vec3 ac = (a + c) / 2.0;
		vec3 ad = (a + d) / 2.0;
		vec3 bc = (b + c) / 2.0;
		vec3 bd = (b + d) / 2.0;
		vec3 cd = (c + d) / 2.0;

		divide_tetra(a, ab, ac, ad, k - 1);
		divide_tetra(ab, b, bc, bd, k - 1);
		divide_tetra(ac, bc, c, cd, k - 1);
		divide_tetra(ad, bd, cd, d, k - 1);
	}
	else {
		tetra(a, b, c, d);
	}
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the window
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);    // draw the TRIANGLES
	glFlush();
}

void init() {
	vec3 a = vec3(-1.0, -1.0,-1.0);
	vec3 b = vec3(1.0, -1.0, -1.0);
	vec3 c = vec3(0.0, 1.0, -1.0);
	vec3 d = vec3(0.0, 0.0, 1.0);
	divide_tetra(a, b, c, d,NumtimesToSubdivide);



	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), NULL, GL_STATIC_DRAW);


	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);

	// Load shaders and use the resulting shader program
	GLuint program = InitShader("vshader02.glsl", "fshader02.glsl");
	glUseProgram(program);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));


	GLuint loc2 = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc2);
	glVertexAttribPointer(loc2, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points)));

	glClearColor(1.0, 1.0, 1.0, 1.0); // white background


}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);


	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE | GLUT_DEPTH);
	glEnable(GL_DEPTH_TEST);
	glutInitWindowSize(640, 480);//��ʾ���ڵĴ�С
	//glutInitWindowPosition(0, 0);//��ʾ���ڵ�λ��

	//glutInitContextVersion(3, 2);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

	glutCreateWindow("Sierpinski Gasket");

	glewExperimental = GL_TRUE;
	glewInit();


	init();


	glutDisplayFunc(display);



	glutMainLoop();
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
