#include<GL/glut.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

void displayPoint(int x,int y)
{
	glColor3f(0,1,0);
	glPointSize(2);
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

float x01,x2,y01,y2;
int ch;

void SimpleDDALine(float x1,float y1,float x2,float y2)
{
	float step;	
	float dx = x2-x1;
	float dy = y2-y1;
	
	
	if(abs(dx)>=abs(dy))
	{
		step = abs(dx);
	}
	else
		step = abs(dy);
		
	float Xinc = dx/step;
	float Yinc = dy/step;
	float x = x1;
	float y = y1;
	
	for(int i=0;i<=step;i++)
	{
		displayPoint(x,y);
		x = x + Xinc;
		y = y + Yinc;
	}
	glFlush();
}
	
void DottedDDALine(float x1, float y1,float x2,float y2)
{
	float step;
	
	float dx = x2-x1;
	float dy = y2-y1;
	
	if(abs(dx)>=abs(dy))
	{
		step = abs(dx);
	}
	else
		step = abs(dy);
	
	float Xinc = dx/(float)step;
	float Yinc = dy/(float)step;
	float x = x1;
	float y = y1;
	
	for(int i=0;i<=step;i++)
	{	
		if(i%3==0)
		displayPoint(x,y);
		x = x + Xinc;
		y = y + Yinc;
	}
	glFlush();
}

void DashedDDALine(float x1,float y1,float x2,float y2)
{
	float step;
	int count=0;
	
	float dx = x2-x1;
	float dy = y2-y1;
	
	if(abs(dx)>=abs(dy))
	{
		step = abs(dx);
	}
	else
		step = abs(dy);
		
	float Xinc = dx/(float)step;
	float Yinc = dy/(float)step;
	float x = x1;
	float y = y1;
	
	for(int i=0;i<=step;i++)
	{
		count++;
		if(count<=15)
		{
			displayPoint(x,y);
			x = x + Xinc;
			y = y + Yinc;
		}
		else if(count<=20 && count>15)
		{
			x = x + Xinc;
			y = y + Yinc;
		}
		else
		{
			count=0;
		}
	}
	glFlush();
}

void mouse(int button, int state, int x,int y)
{
	static int xst,yst,pt=0;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if(pt==0)
		{
			xst = x;
			yst = y;
			x01 = xst;
			y01 = yst;
			pt = 1;
		}
		else 
		{
			if(ch==1)
			{
				SimpleDDALine(xst,yst,x,y);
			}
			else if(ch==2)
			{
				DottedDDALine(xst,yst,x,y);
			}
			else if(ch==3)
			{
				DashedDDALine(xst,yst,x,y);
			}
			xst = x;
			yst = y;
		}
	}
	else if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		pt=0;
		glFlush();
	}	
}


void keyboard(unsigned char key,int x,int y)
{
	switch(key)
	{
		case '1':
		{
			ch = 1;
			glutMouseFunc(mouse);
			break;
		}
		case '2':
		{
			ch = 2;
			glutMouseFunc(mouse);
			break;
		}
		case '3':
		{
			ch = 3;
			glutMouseFunc(mouse);
			break;
		}
	}
	glutPostRedisplay();
}

void display(void)
{
	glColor3f(1,0,0);
	SimpleDDALine(0,300,600,300);
	SimpleDDALine(300,0,300,600);
	glutKeyboardFunc(keyboard);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutCreateWindow("Window New");
	glClearColor(1.0,1.0,1.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(0,600,600,0);
	
	cout<<"1. Simple Line";
	cout<<"2. Dotted Line";
	cout<<"3. Dashed Line";
	
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
