#include "game.h"

//variables
static float xSpeed = 0.3;
static float ySpeed = 0.3;
static float speed = 0.3;

char str[100];
static int mouseX = 0;
int pcResult = 0;
int playerResult = 0;

RECTANGLE ball = {100,120,100,120};
RECTANGLE player = {0,40,490,500};
RECTANGLE wall;

//draws the rectangles
void drawRectangle(RECTANGLE rect){
    glBegin(GL_QUADS);
    glVertex2f(rect.left, rect.bottom);        //left bottom 
    glVertex2f(rect.left, rect.top);           //left top
    glVertex2f(rect.right, rect.top);          //right top
    glVertex2f(rect.right, rect.bottom);       //right bottom
    glEnd();
}

//prints text           --> source of line 28 to 36: https://flex.phys.tohoku.ac.jp/texi/glut/glutStrokeCharacter.3xglut.html
void output(GLfloat x, GLfloat y, char* text){
    char* p;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(0.1, -0.1, 1);
    for (p = text; *p; p++)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
    glPopMatrix();
}

//tests if ball hits wall
std::string testBallWall(RECTANGLE  ball, RECTANGLE wall){
    if (ball.right >= wall.right)
        return "right";
    if (ball.left <= wall.left)
        return "left";
    if (ball.top <= wall.top)
        return "top";
    if (ball.bottom >= wall.bottom)
        return "bottom";
    else return "";
}

//tests if ball hits player
bool testBallPlayer(RECTANGLE ball, RECTANGLE player){
    if (ball.bottom >= player.top && ball.left >= player.left-10 && ball.right <= player.right+10){
        playerResult++;
        speed += 0.01;
        return true;
    }
    return false;
}

//closes window if ESC is pressed
void keyboard(unsigned char button, int x, int y){
    if (button == 27)
        exit(0);
}

//tracks mouse movement on the x axis
void mouse(int x, int y){
    mouseX = x;
}

//loop of ball movement
void ballMovement(int t) {
    ball.left += xSpeed;
    ball.right += xSpeed;
    ball.top += ySpeed;
    ball.bottom += ySpeed;

    glutTimerFunc(1, ballMovement, 1);
}

//is called once at initialization and if the window size is changed
void reshape(int x, int y){
    windowX = x;
    windowY = y;
    player.top = y - 10;
    player.bottom = y;

    glViewport(0, 0, (GLsizei)x, (GLsizei)y);               //source of line 89 to 93: https://www.swiftless.com/tutorials/opengl/reshape.html
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, x, y, 0);
    glMatrixMode(GL_MODELVIEW);
}

//puts everything on the display
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    sprintf_s(str, "PC : %d ", pcResult);
    output(10, 80, str);
    sprintf_s(str, "Player : %d ", playerResult);
    output(10, 120, str);

    wall.left = wall.top = 0;
    wall.right = windowX;
    wall.bottom = windowY;

    drawRectangle(ball);

    if (testBallWall(ball, wall) == "right")
        xSpeed = -speed;
    if (testBallWall(ball, wall) == "left")
        xSpeed = speed;
    if (testBallWall(ball, wall) == "top")
        ySpeed = speed;
    if (testBallWall(ball, wall) == "bottom") {
        speed = 0.3;
        ySpeed = -speed;
        pcResult++;
    }

    drawRectangle(player);
    player.left = mouseX - 30;
    player.right = mouseX + 30;

    if (testBallPlayer(ball, player) == true)
        ySpeed = -speed;

    glutSwapBuffers();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pong Game");
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutTimerFunc(1, ballMovement, 1);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouse);
    glutMainLoop();

    return 0;
}