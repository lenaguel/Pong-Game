#include <include/GL/glut.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string>

//variables
static int windowX, windowY;

struct RECTANGLE {
    float left, right, top, bottom;
};

void drawRectangle(RECTANGLE rect);

//prints text          
void output(GLfloat x, GLfloat y, char* text);

//tests if ball hits wall
std::string testBallWall(RECTANGLE  ball, RECTANGLE wall);

//tests if ball hits player
bool testBallPlayer(RECTANGLE ball, RECTANGLE player);

//closes window if ESC is pressed
void keyboard(unsigned char button, int x, int y);

//tracks mouse movement on the x axis
void mouse(int x, int y);

//loop of ball movement
void ballMovement(int t);

//is called once at initialization and if the window size is changed
void reshape(int x, int y);

//puts everything on the display
void display();
