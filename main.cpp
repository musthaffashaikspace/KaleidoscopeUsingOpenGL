#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<cmath>
#include<time.h>
#include <GL/glut.h> // (or others, depending on the system in use)
GLfloat trivert[10000][6]={{900,800,1100,800,1000,900}};
GLfloat circvert[900][2]={{1900,1000}};
int times=0;
int nooftriangles=1;
int noofcircles=1;
static int p=0;
int tristartx,tristarty,circstartx,circstarty;
void initialize_start_points(void)
{
    srand(time(0));
    circvert[0][0]=rand()%2000;
    circvert[0][1]=rand()%2000;
    circstartx=circvert[0][0];
    circstarty=circvert[0][1];
    trivert[0][0]=rand()%2000;
    trivert[0][1]=rand()%2000;
    tristartx=trivert[0][0];
    tristarty=trivert[0][1];
    trivert[0][2]=trivert[0][0]+200;
    trivert[0][3]=trivert[0][1];
    trivert[0][4]=(trivert[0][0]+trivert[0][2])/2;
    trivert[0][5]=trivert[0][1]+100;
}
void circle(GLfloat x, GLfloat y, GLdouble radius) {
	float x2, y2;
	float angle;
	glPointSize(2.0);
	glBegin(GL_TRIANGLE_FAN);
	for (angle = 0.0; angle < 6.3; angle += 0.01)
	{
		x2 = x + sin(angle)*radius;
		y2 = y + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glFlush();
	glEnd();
}
void drawcircles(void)
{
    glColor3f(0,0,1);
    for(int i=0;i<noofcircles;i++)
    {
        circle(circvert[i][0],circvert[i][1],50);
    }
    glFlush();
}
void init (void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0); // Set display-window color to black.
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode (GL_PROJECTION); // Set projection parameters.
    gluOrtho2D (0.0, 2000.0, 0.0, 2000.0);
}
GLfloat pointrefline1(GLfloat y)
{
    return -2*(y-700)+y;
}
GLfloat pointrefline2x(GLfloat x,GLfloat y)
{
    GLfloat t=(-3.464*x-2*y+5903.2)/3.999;
    return t*1.732+x;
}
GLfloat pointrefline2y(GLfloat x,GLfloat y)
{
    GLfloat t=(-3.464*x-2*y+5903.2)/3.999;
    return t+y;
}
GLfloat pointrefline3x(GLfloat x,GLfloat y)
{
    GLfloat t=(-3.464*x+2*y+1024.8)/3.999;
    return t*1.732+x;
}
GLfloat pointrefline3y(GLfloat x,GLfloat y)
{
    GLfloat t=(3.464*x-2*y-1024.8)/3.999;
    return t+y;
}
void drawtriangles(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i=0;i<=nooftriangles;i++)
    {
        glColor3f(1,0,0);
        glBegin(GL_TRIANGLES);
        for(int j=0;j<6;j+=2){
                glVertex2f(trivert[i][j],trivert[i][j+1]);
        }
    }
    glFlush();
    glEnd();
}
void reflect1(void)
{

    int y=nooftriangles*2;
    for(int j=nooftriangles,i=0;j<y&&i<nooftriangles;j++,i++)
    {
        trivert[j][0]=trivert[i][0];
        trivert[j][1]=pointrefline1(trivert[i][1]);
        trivert[j][2]=trivert[i][2];
        trivert[j][3]=pointrefline1(trivert[i][3]);
        trivert[j][4]=trivert[i][4];
        trivert[j][5]=pointrefline1(trivert[i][5]);
    }
    nooftriangles*=2;
    drawtriangles();
}
void reflect2(void)
{
    int y=nooftriangles*2;
    for(int j=nooftriangles,i=0;j<y&&i<nooftriangles;j++,i++)
    {
        trivert[j][0]=pointrefline2x(trivert[i][0],trivert[i][1]);
        trivert[j][1]=pointrefline2y(trivert[i][0],trivert[i][1]);
        trivert[j][2]=pointrefline2x(trivert[i][2],trivert[i][3]);
        trivert[j][3]=pointrefline2y(trivert[i][2],trivert[i][3]);
        trivert[j][4]=pointrefline2x(trivert[i][4],trivert[i][5]);
        trivert[j][5]=pointrefline2y(trivert[i][4],trivert[i][5]);
    }
    nooftriangles*=2;
    drawtriangles();
}
void reflect3(void)
{
    int y=nooftriangles*2;
    for(int j=nooftriangles,i=0;j<y&&i<nooftriangles;j++,i++)
    {
        trivert[j][0]=pointrefline3x(trivert[i][0],trivert[i][1]);
        trivert[j][1]=pointrefline3y(trivert[i][0],trivert[i][1]);
        trivert[j][2]=pointrefline3x(trivert[i][2],trivert[i][3]);
        trivert[j][3]=pointrefline3y(trivert[i][2],trivert[i][3]);
        trivert[j][4]=pointrefline3x(trivert[i][4],trivert[i][5]);
        trivert[j][5]=pointrefline3y(trivert[i][4],trivert[i][5]);
    }
    nooftriangles*=2;
    drawtriangles();
}
 void reflectcirc1(void)
 {
    int y=noofcircles*2;
    for(int j=noofcircles,i=0;j<y&&i<noofcircles;j++,i++)
    {
        circvert[j][0]=circvert[i][0];
        circvert[j][1]=pointrefline1(circvert[i][1]);
    }
    noofcircles*=2;
    drawcircles();
 }
  void reflectcirc2(void)
 {
    int y=noofcircles*2;
    for(int j=noofcircles,i=0;j<y&&i<noofcircles;j++,i++)
    {
        circvert[j][0]=pointrefline2x(circvert[i][0],circvert[i][1]);
        circvert[j][1]=pointrefline2y(circvert[i][0],circvert[i][1]);
    }
    noofcircles*=2;
    drawcircles();
 }
 void reflectcirc3(void)
 {
    int y=noofcircles*2;
    for(int j=noofcircles,i=0;j<y&&i<noofcircles;j++,i++)
    {
       circvert[j][0]=pointrefline3x(circvert[i][0],circvert[i][1]);
       circvert[j][1]=pointrefline3y(circvert[i][0],circvert[i][1]);
    }
    noofcircles*=2;
    drawcircles();
 }
void display(void)
{
    glClearColor(0,0,0,0);
    glViewport(200,100,900,400);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnd();
    if(p>=1)
    {
        for(int u=0;u<10;u++)
        {
            initialize_start_points();
            while(tristartx>-1000&&tristarty>-1000&&circstartx<3000&&circstarty<3000)
            {
                circvert[0][0]=circstartx;
                circvert[0][1]=circstarty;
                trivert[0][1]=tristartx;
                trivert[0][2]=tristarty;
                trivert[0][2]=trivert[0][0]+200;
                trivert[0][3]=trivert[0][1];
                trivert[0][4]=(trivert[0][0]+trivert[0][2])/2;
                trivert[0][5]=trivert[0][1]+100;
                glClear(GL_COLOR_BUFFER_BIT);
                nooftriangles=1;
                noofcircles=1;
                for(int k=0;k<4;k++)
                {
                    reflect1();
                    reflect2();
                    reflect3();
                }
                glColor3f(0,0,1);
                for(int k=0;k<3;k++)
                {
                    reflectcirc1();
                    reflectcirc2();
                    reflectcirc3();
                }
                circstartx+=30;
                tristartx-=30;


            }
        }
    }
    p++;
    glFlush();
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv); // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Set display mode.
    glutInitWindowPosition (0, 0); // Set top-left display-window position.
    glutInitWindowSize (1200, 600); // Set display-window width and height.
    glutCreateWindow ("Alpha Ray Scattering Experiment"); // Create displaywindow.
    init ( ); // Execute initialization procedure.
    glutDisplayFunc (display);
    glutMainLoop ( ); // Display everything and wait.
}
