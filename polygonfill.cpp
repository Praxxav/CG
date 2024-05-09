#include<GL/glut.h>
#include<iostream>

using namespace std;

int ww=600,wh=500,ch;
float intcolor[3]={1,1,1};
float fillcol[3]={1,0,0};
float fillcolor[3]={0,0,1};
float bordercolor[3]={1,0,0};

void setPixel(int pointx,int pointy, float f[3])
{
	glBegin(GL_POINTS);
	glColor3fv(f);
	glVertex2i(pointx,pointy);
	glEnd();
	glFlush();
}

void getPixel(int x,int y, float pixels[3])
{
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pixels);
}

void drawPolygon(int x1,int y1,int x2,int y2)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1,y1);
	glVertex2i(x1,y2);
	glVertex2i(x2,y2);
	glVertex2i(x2,y1);
	glEnd();
	glFlush();
}

void display()
{
	glFlush();
}

void floodfill4(int x, int y, float oldcolor[3], float newcolor[3])
{
	float color[3];
	getPixel(x,y,color);
	
	if(color[0]==oldcolor[0] && color[1]==oldcolor[1] && color[2]==oldcolor[2])
	{
		setPixel(x,y,newcolor);
		floodfill4(x+1,y,oldcolor,newcolor);
		floodfill4(x-1,y,oldcolor,newcolor);
		floodfill4(x,y+1,oldcolor,newcolor);
		floodfill4(x,y-1,oldcolor,newcolor);
	}
}

void boundaryfill4(int x,int y, float fillcolor[3],float bordercolor[3])
{
	float interiorcolor[3];
	getPixel(x,y,interiorcolor);
	
	if((interiorcolor[0]!=fillcolor[0] || interiorcolor[1] != fillcolor[1] || interiorcolor[2] != fillcolor[2]) && (interiorcolor[0] != bordercolor[0] || interiorcolor[1] != bordercolor[1] || interiorcolor[2] != bordercolor[2]))
	{
		setPixel(x,y,fillcolor);
		boundaryfill4(x+1,y,fillcolor,bordercolor);
		boundaryfill4(x-1,y,fillcolor,bordercolor);
		boundaryfill4(x,y+1,fillcolor,bordercolor);
		boundaryfill4(x,y-1,fillcolor,bordercolor);
	}
}

void mouse(int btn, int state, int x, int y)
{	
	if(btn==GLUT_LEFT_BUTTON &&  state==GLUT_DOWN)
	{
		int xi=x;
		int yi=(wh-y);
		
		if(ch==1)
		{
			floodfill4(xi,yi,intcolor,fillcol);	
		}
		if(ch==2)
		{
			boundaryfill4(xi,yi,fillcolor,bordercolor);
		}
	glFlush();
	}
}

void keyboard(unsigned char key,int x, int y)
{
	switch(key)
	{
		case 'f':
		ch=1;
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0,0,0);
		drawPolygon(150,250,200,300);
		glutMouseFunc(mouse);
		break;
		
		case 'b':
		ch=2;
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1,0,0);
		drawPolygon(150,250,200,300);
		glutMouseFunc(mouse);
		break;
	}
	glutPostRedisplay();
}

void myinit()
{	
	glViewport(0,0,ww,wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,(GLdouble)ww,0,(GLdouble)wh);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1,1,1,1);
	glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(ww,wh);
	glutCreateWindow("new window");
	myinit();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	cout<<"f. flood";
	cout<<"b. border";	
	glutMainLoop();
	return 0;
}
