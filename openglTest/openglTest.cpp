// openglTest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include <windows.h> 
#include <GL/gl.h>  
#include <GL/glu.h>  
#include <GL/glut.h> 


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
	glClearColor(0.0, 1.0, 0.0, 1.1);//申明一个刷新的颜色
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

int main(int argc, char** argv) {
	glutInit(&argc, argv);//初始化openGl
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);//显示窗口的位置
	glutInitWindowSize(350, 150);//显示窗口的大小
	glutCreateWindow("kry interaction");//表示用键盘来进行交互的

	init();//自定义的方法
	glutDisplayFunc(display);//绘制函数
	glutKeyboardFunc(myKayBoard);//点击键盘的时候就会调用该方法
	glutMainLoop();
	return 0;
}
