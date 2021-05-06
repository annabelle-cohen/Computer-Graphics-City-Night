#include "glut.h"
#include <math.h>
#include <time.h>

const int LIGHTS = 40;
bool winLight[LIGHTS][LIGHTS];
double offset = 0.01;

const int NUM_STARS = 100;

typedef struct
{
	double x, y;
}POINT2D;

POINT2D stars[NUM_STARS];


void init()
{	//(Red,Green,Blue,alpha)
	glClearColor(0.0, 0.6, 0.8, 0);// color of window background

	//define main axes
	glOrtho(-1, 1, -1, 1, -1, 1);

	for (int i = 0; i < NUM_STARS; i++) {
		stars[i].y = ((rand() % 1000) / 500.0) - 1;
		stars[i].x= ((rand() % 1000) / 500.0) - 1;
	}

	srand(time(0));//seed or init random numbers generetor

	//init the windows lights randomly
	for (int i = 0; i < LIGHTS; i++)
		for (int j = 0; j < LIGHTS; j++)
			winLight[i][j] = !(rand() % 3 == 0);//1/3 of the lights will be off while 2/3 wil be on

}

void DrawBuilding(double left, double height, double width, bool reflection)
{	
	//Building
	if (reflection)
		height = -height;

	glBegin(GL_POLYGON);

	if (!reflection)
		glColor3d(fabs(left-0.1), fabs(height-0.1), 0.3);
	else
		glColor3d(fabs(left)/2, fabs(height)/2, 0.15);

	glVertex2d(left, height);
	glVertex2d(left + width, height);
	
	if (reflection)
		glColor3d(0.4, 0.4, 0.4);
	else
		glColor3d(0.7, 0.8, 0.8);

	glVertex2d(left + width, 0);
	glVertex2d(left,0);
		
	glEnd();

	//windows 
	double floor = 0.01;
	double h, x;
	int i, j;
	double height1 = fabs(height);
	glColor3d(1, 1, 0);
	glBegin(GL_POINTS);
	for (h = height1 - 2 * floor, i = 0; h >= 2 * floor; h -= 2 * floor, i++)
	{
		for (x = left + floor, j = 0; x <= left + width - floor; x += floor, j++) {
			if (winLight[i][j]) {
				if (!reflection)
					glVertex2d(x, h);
				else
					glVertex2d(x, -h);
			}
		}

	}
	glEnd();

}


void ThirdLineOfBuildings()
{
	double x, y;
	double step = 0.07;

	
	//lines that give us sine move
	for (x = -1; x <= 1; x += step)
	{	
		y = fabs(0.2 * sin(5 * x - offset));

		DrawBuilding(x, y, step - offset, false);
		//water reflecation
		DrawBuilding(x, y, step - offset, true);
	}

}

void SecondBuildingLine()
{
	double x, y;
	double step = 0.1;

	for (x = -1; x <= 1; x += step)
	{

		y = fabs(0.2 * sin(6 * x - offset)+0.4);
		DrawBuilding(x, y, step - offset, false);
		//water reflaction
		DrawBuilding(x, y, step - offset, true);
	}

}



void DrawBackground()
{
	glBegin(GL_POLYGON);
		
	glColor3d(0.3, 0, 0.4);
		glVertex2d(-1, 1);//top sky point
		glVertex2d(1, 1);
		//bottom
		glColor3d(0.5 , 0.6 , 0.7);
		glVertex2d(1, 0);//ground point
		glVertex2d(-1, 0);		
	glEnd();

	//water reflecation
	glBegin(GL_POLYGON);
	glColor3d(0.4 , 0.4 , 0.8);
	glVertex2d(1, 0);//ground point
	glVertex2d(-1, 0);

	//bottom
	glColor3d(0 , 0 , 0.1);
	glVertex2d(-1, -1);
	glVertex2d(1, -1);//ground point	
	glEnd();

}

void DrawStars()
{	
	
	glBegin(GL_POINTS);
	for (int i = 0; i < NUM_STARS; i++) {
		if (stars[i].y < 0)
			stars[i].y = -stars[i].y;
		glColor3d(1, 1, 0);
		glVertex2d(stars[i].x, stars[i].y);
		glColor3d(0.8, 0.8, 0.8);
		glVertex2d(stars[i].x, -stars[i].y);
	}
	glEnd();
}

void DrawWindow(double left, double height, double width, bool reflection)
{

	//windows 
	double floor = 0.01;
	double h,x;
	int i, j;
	double height1 = fabs(height);
	glColor3d(1, 1, 0);
	glBegin(GL_POINTS);
	for (h = height1 - 2 * floor,i=0; h >= 2 * floor; h -= 2 * floor,i++)
	{
		for ( x = left + floor, j=0; x <= left + width - floor; x += floor,j++) {
			if (winLight[i][j]) {
				if (!reflection)
					glVertex2d(x, h);
				else
					glVertex2d(x, -h);
			}
		}
		
	}
	glEnd();
}

void FirstBuilding()
{

	DrawBuilding(-0.04, 0.8, 0.08, false);
	
	//roof
	glBegin(GL_POLYGON);
	glColor3d(fabs(0.04), fabs(0.8), 0.3);
	glVertex2d(-0.02, 0.8);
	glColor3d(fabs(0.5), fabs(0.7), 0.4);
	glVertex2d(-0.02, 0.83);
	glVertex2d(0.02, 0.83);
	glVertex2d(0.02, 0.8);
	glEnd();

	//antenna
	glLineWidth(2);
	glBegin(GL_LINE_STRIP);
	glVertex2d(0.0, 0.83);
	glVertex2d(0.0, 0.87);
	glEnd();

	DrawWindow(-0.04, 0.8, 0.08, false);

	//reflaction
	glBegin(GL_LINE_STRIP);

	glColor3d(0.4, 0.4, 0.4);
	glVertex2d(0.0, -0.83);
	glVertex2d(0.0,-0.87);
	glEnd();

	glColor3d(fabs(0.04/2), fabs(0.8/2), 0.15);
	glBegin(GL_POLYGON);
	glVertex2d(-0.02, -0.8);
	glVertex2d(-0.02, -0.83);
	glVertex2d(0.02, -0.83);
	glVertex2d(0.02, -0.8);
	glEnd();

	DrawBuilding(-0.04, 0.8, 0.08, true);


}

void DrawFlashlights() 
{
	double offset = 0.1;
	double width = 0.005;
	double height = 0.05;
	double lightWidth = 0.01;
	
	for (double i = -1; i <= 1; i += offset) {
		glBegin(GL_POLYGON);
		glColor3d(0.2 , 0.2 , 0.2);
		glVertex2d(i, 0);
		glVertex2d(i, height);
		glVertex2d(i + width, height);
		glVertex2d(i + width, 0);
		glVertex2d(i, -height);
		glVertex2d(i + width, -height);
		glEnd();
		
		glBegin(GL_LINE_STRIP);
			glColor3d(0.2, 0.2, 0.2);
			glLineWidth(3);
			glVertex2d(i + width, height);
			glVertex2d(i + width+width, height);
		glEnd();

		glBegin(GL_LINE_STRIP);
		glColor3d(1, 1, 1);
		glVertex2d(i + width, height-height*0.1);
		glVertex2d(i + width + width, height);
		glEnd();
		


		glBegin(GL_LINE_STRIP);
		glColor3d(0.2, 0.2, 0.2);
		glLineWidth(3);
		glVertex2d(i + width, -height);
		glVertex2d(i + width + width, -height);
		glEnd();

		glBegin(GL_LINE_STRIP);
		//glPointSize(20);
		glColor3d(1, 1, 1);
		glVertex2d(i + width,  height * 0.1 -height );
		glVertex2d(i + width + width,-height);
		glEnd();
	}
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	DrawBackground();
	
	DrawStars();

	FirstBuilding();

	SecondBuildingLine();
	
	//draw function graph 
	ThirdLineOfBuildings();

	DrawFlashlights();

	glutSwapBuffers(); // show all
}

void idle()
{
	
	int row, col;
	row = rand() % LIGHTS;
	col = rand() % LIGHTS;

	//randomly changes lights
	winLight[row][col] = !winLight[row][col];

	glutPostRedisplay(); //post meassge(with request to show the frame) to main window 
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("First Example");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	init();

	glutMainLoop();
}