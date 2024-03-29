/*= ================================================================================================ =
PROGRAMMER: Trey Alexander 50% (primary 3d model, secondary 3d model, secondary 3d model window, 3d model movement, 3d model menu, presentation),
    Tyler Glick 25% (2d plane, final 3d model positioning, presentation), Ethan Tanner 25% (2d text creation, 2d text menu, 2d text operations)
COURSE : CSC 525/625
MODIFIED BY : N/A
LAST MODIFIED DATE : 5/16/2022
DESCRIPTION : Interactive 3D ad for a pokeball model
NOTE :
FILES : Project3_Team2.cpp
IDE/COMPILER : MicroSoft Visual Studio 2019
INSTRUCTION FOR COMPILATION AND EXECUTION :
1.
Double click on Project3_Team2.sln
to OPEN the project
2.
Press Ctrl + F7
to COMPILE
3.
Press Ctrl + F5
to EXECUTE
==================================================================================================*/
void menu(int value);

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string>
#define drawOneLine(x1,y1,x2,y2) glBegin(GL_LINES); \
glVertex2f ((x1),(y1)); glVertex2f((x2),(y2)); glEnd(); // for line drawing
void pokeball();
void openPokeball();

GLuint mybody; // Create Variables
const GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };

static int head = 0, a = 0, s = 0, rear = -90, lear = -90, body = 0, lleg = -90, rleg = -90, ball = 0, stage = 0;
GLfloat ballRadius = 0.1f;
static int slices = 100;
static int stacks = 100;

float angle = 0.0f;
float handAngle[2] = { 0.0f, 0.0f };
float legAngle[2] = { 0.0f,0.0f };
float baseAngle[2] = { 0.0f,0.0f };

int refreshMills = 30;


bool isTime, isInfo, isContact = false;

void myInit();
int openBallWindow();
float ver[8][3] =
{
    {-1.0,-1.0,1.0},
    {-1.0,1.0,1.0},
    {1.0,1.0,1.0},
    {1.0,-1.0,1.0},
    {-1.0,-1.0,-1.0},
    {-1.0,1.0,-1.0},
    {1.0,1.0,-1.0},
    {1.0,-1.0,-1.0},
};

GLfloat color[8][3] =
{
    {0.0,1.0,1.0},
    {0.0,0.0,1.0},
    {0.0,0.0,1.0},
    {0.0,0.0,1.0},
    {0.0,0.0,1.0},
    {1.0,1.0,0.0},
    {1.0,1.0,0.0},
    {1.0,1.0,0.0},
};

//*******************************************************************************************

void mainpart() {

    glColor3d(0.5, 0.85, 0.88);  // body
    glTranslatef(0, -0.05, 1.1);
    glPushMatrix();
    glRotated((GLfloat)body, 1, 0, 0);
    glutSolidSphere(0.3, 40, 50);
    glPopMatrix();

    glEnd();

    // prepare for drawing the geometry
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

//*******************************************************************************************

double rotate_y = -25;
double rotate_x = -30;
double rotate_z = 0;

void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT) //rotate the model depending on the keys pressed
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    else if (key == GLUT_KEY_F1)
        rotate_z += 5;
    else if (key == GLUT_KEY_F2)
        rotate_z -= 5;
    glutPostRedisplay();
}

void sphere()
{
    // Create a new quadric and render it normally
    GLUquadricObj* pObj = gluNewQuadric();
    gluQuadricDrawStyle(pObj, GLU_FILL);
    gluSphere(pObj, 0.5f, 1.0f, 1.0f);
}

//*******************************************************************************************

double x1 = 3;
double x2 = 2;
double x3 = 3;
double x4 = -1;
double x5 = -1;
double x6 = -1;
double x7 = 3;
double x8 = 4;
double x9 = 2;

void display()
{
    glClearColor(0.30, 0.35, 0.45, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 0);
    // specify a background color: white 

    gluOrtho2D(-200, 200, -200, 200); // specify a viewing area

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
        x1, x2, x3,
        x4, x5, x6,
        x7, x8, x9
    );

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);
    pokeball(); // call the function for drawing the pokeball

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 600, 0.0, 450); // create a flat plane for drawing text
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(220, 370);
    std::string s = "New Pokeball Model!";
    void* font = GLUT_BITMAP_HELVETICA_18;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c); // draw the text on screen
    }
    glRasterPos2i(135, 355);
    s = "Right click to bring up the menu, or use the arrow keys to move the ball around!";
    font = GLUT_BITMAP_HELVETICA_10;
    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }

    if (isTime) {
        glRasterPos2i(15, 79);
        s = "The model will release on July 15, 2022.";
        font = GLUT_BITMAP_HELVETICA_12;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
    }
    if (isInfo) {
        glRasterPos2i(15, 63);
        s = "Pokeballs are for catching the mysterious creatures known as Pokemon!";
        font = GLUT_BITMAP_HELVETICA_12;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        glRasterPos2i(15, 47);
        s = "This model acts to recreate Pokeballs in a 1-1 scale.";
        font = GLUT_BITMAP_HELVETICA_12;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
        glRasterPos2i(15, 31);
        s = "They are 3D printed, and then details are hand painted.";
        font = GLUT_BITMAP_HELVETICA_12;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
    }
    if (isContact) {
        glRasterPos2i(15, 15);
        s = "For any questions, email help@pkmnmodel.com";
        font = GLUT_BITMAP_HELVETICA_12;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i)
        {
            char c = *i;
            glutBitmapCharacter(font, c);
        }
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glFlush();

    glutSwapBuffers();
}

//*******************************************************************************************

void pokeball() {
    glColor3d(1.0, 0, 0);  // pokeball(red)
    glPushMatrix();
    glTranslated(0, -0.7, 0);
    glRotated((GLfloat)ball, 0, 0, 0);
    glutSolidSphere(1, slices, stacks);
    glPopMatrix();

    glColor3d(0.0, 0.0, 0.0);  // pokeball(black)
    glPushMatrix();
    glTranslated(0, -0.7, 0.04);
    glRotated(0, 0, 0, 0);
    glutSolidSphere(0.70, slices, stacks);
    glPopMatrix();


    glColor3d(.9, .9, .9);  // pokeball(small white)
    glPushMatrix();
    glTranslated(0.8, -0.70, 0.50);
    glRotated(0, 0, 0, 0);
    glutSolidSphere(0.30, slices, stacks);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0);  // pokeball(big white)
    glPushMatrix();
    glTranslated(0, -0.71, 0);
    glRotated(0, 0, 0, 0);
    glutSolidSphere(1.0, slices, stacks);
    glPopMatrix();

    glColor3d(0.0, 0.0, 0.0);  // pokeball TORUS
    glPushMatrix();
    glTranslated(0, -0.7, 0);
    glRotated(90, 1, 0, 0);
    glutSolidTorus(0.10, 1.0, slices, stacks);
    glPopMatrix();
}

//*******************************************************************************************

void openBallDisplay()
{
    glClearColor(0.30, 0.35, 0.45, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1, 1, 1, 0); // specify a background clor: white 

    gluOrtho2D(-200, 200, -200, 200); // specify a viewing area

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
        x1, x2, x3,
        x4, x5, x6,
        x7, x8, x9
    );

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    openPokeball();

    glutSwapBuffers();
}

//*******************************************************************************************

void openPokeball() {


    glColor3d(0.0, 0.0, 1.0);  // voltorb red
    glPushMatrix();
    glTranslated(0, -0.7, 0.04);
    glRotated(0, 0, 0, 0);
    glutSolidSphere(0.70, slices, stacks);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0);  // voltorb white
    glPushMatrix();
    glTranslated(0, -0.71, 0.04);
    glRotated(0, 0, 0, 0);
    glutSolidSphere(0.7, slices, stacks);
    glPopMatrix();

    glColor3d(1.0, 1.0, 1.0);  //eyes
    glPushMatrix();
    glTranslated(.47, -0.3, 0.35);
    glRotated(1, 0, 0, 0);
    glScalef(1.5, 1.1, 1.1);
    glutSolidCube(0.1);
    glPopMatrix();

    glPushMatrix();      //eyes
    glTranslated(0.47, -0.3, -0.25);
    glRotated(0, 0, 0, 2);
    glScalef(1.5, 1.1, 1.1);
    glutSolidCube(0.1);
    glPopMatrix();
}

//**********************************************************************************************

void perspectiveDisplay()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60.0f, (w / h), 0.1, 90);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
        2, 2, 2,
        0, 0, 0,
        0, 0, 1
    );

    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
    glRotatef(rotate_z, 0.0, 0.0, 1.0);

    glutSwapBuffers();
}

//**********************************************************************************************

void myInit()
{

    glClearColor(0, 1, 1, 0); // specify a background clor: white 

    gluOrtho2D(-200, 200, -200, 200); // specify a viewing area
}

//*******************

void menu(int value) {
    switch (value)
    {
    case 7: // Reset
        rotate_x = -30;
        rotate_y = -25;
        rotate_z = 0;
        x1 = 3;
        x2 = 2;
        x3 = 3;
        x4 = -1;
        x5 = -1;
        x6 = -1;
        x7 = 3;
        x8 = 4;
        x9 = 2;
        break;

    case 8: // exit the code
        exit(0);
        break;

    case 10: // render in Perspective zoom out
        x1 += 1;
        x2 += 1;
        x3 += 1;
        x4 += 1;
        x5 += 1;
        x6 += 1;
        x7 += 1;
        x8 += 1;
        x9 += 1;
        perspectiveDisplay();
        break;

    case 11: // render in Perspective zoom in
        x1 -= 1;
        x2 -= 1;
        x3 -= 1;
        x4 -= 1;
        x5 -= 1;
        x6 -= 1;
        x7 -= 1;
        x8 -= 1;
        x9 -= 1;
        perspectiveDisplay();
        break;

    case 12: // open ball window
        openBallWindow();
        break;

    case 13: // open date and time window
        if (isTime) {
            isTime = false;
        }
        else {
            isTime = true;
        }
        break;

    case 14: // rules and format window
        if (isInfo) {
            isInfo = false;
        }
        else {
            isInfo = true;
        }
        break;

    case 15: // contact window
        if (isContact) {
            isContact = false;
        }
        else {
            isContact = true;
        }
        break;
    }



    glutPostRedisplay();
}

//***********************************************************

int openBallWindow()
{
    //  glutInit(&argc, argv);
    myInit();
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Open Ball View");
    int sub1 = glutCreateMenu(menu); // creating the menus
    glutAddMenuEntry("Zoom out", 10);
    glutAddMenuEntry("Zoom in", 11);
    glutAddMenuEntry("Reset", 7);
    glutAddMenuEntry("Exit", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    //glutDisplayFunc(openBallDisplay);
    glutDisplayFunc(openBallDisplay);
    glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}

//***********************************************************

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    myInit();
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Regular Ball View");

    int sub1 = glutCreateMenu(menu); // creating the menus
    glutAddMenuEntry("Date Info", 13);
    glutAddMenuEntry("Model Info", 14);
    glutAddMenuEntry("Contact Info", 15);
    glutAddMenuEntry("Zoom out", 10);
    glutAddMenuEntry("Zoom in", 11);
    glutAddMenuEntry("Open the Ball!", 12);
    glutAddMenuEntry("Reset", 7);
    glutAddMenuEntry("Exit", 8);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(display); // call display callback
    glutSpecialFunc(specialKeys); // call key callback
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
