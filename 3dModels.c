#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int width;
static int height;
float _angle=0.0;
float _cameraangle=30.0;
float _red = 1.0;
float _green = 1.0;
float _blue = 1.0;
float _X = 0.0;
float _Y = 0.0;
float _Z = 0.0;
float _sX = 1.0;
float _sY = 1.0;
float _sZ = 1.0;

void Desenha(void)
{
    glColor3f(_red, _green, _blue);
    glRotatef(_angle,0.0f,1.0f,0.0f);
    glTranslatef(_X, _Y, _Z);
    glScalef(_sX,_sY,_sZ);
    glutWireCube(1.0);
    // glutWireTeapot(0.5);
    // glutWireCone(1, 1, 10, 10);
    // glutWireTorus(0.5,1.5,10,10);
    // glutWireTetrahedron();
    // glutWireDodecahedron();
    // glutWireOctahedron();
    // glutWireIcosahedron();

}


static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);

    glViewport(0, 0, width/2, height);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, -3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Desenha();

    glViewport(width/2, 0, width/2, height);
    glLoadIdentity();
    gluLookAt(0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0);
    Desenha();

    glFlush();
}

static void reshape(int w, int h) {
    width = w;
    height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Fun��o callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN)
        {
            _angle += 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN)
        {
            _angle -= 5;
        }

    glutPostRedisplay();
}


// Fun��o callback chamada para gerenciar eventos do mouse
void Teclado(int key, int x, int y)
{

    if(key == GLUT_KEY_UP)
        _Y += 0.5;
    
    if(key == GLUT_KEY_DOWN)
        _Y -= 0.5;
        
    if(key == GLUT_KEY_LEFT)
        _X += 0.5;
    
    if(key == GLUT_KEY_RIGHT)
        _X -= 0.5;

    if(key == GLUT_KEY_PAGE_DOWN)
        _Z -= 0.5;
    
    if(key == GLUT_KEY_PAGE_UP)
        _Z += 0.5;

    if(key == GLUT_KEY_F1)
        _red -= 0.1;

    if(key == GLUT_KEY_F2)
        _red += 0.1;

    if(key == GLUT_KEY_F3)
        _green -= 0.1;

    if(key == GLUT_KEY_F4)
        _green += 0.1;

    if(key == GLUT_KEY_F5)
        _blue -= 0.1;

    if(key == GLUT_KEY_F6)
        _blue += 0.1;

    if(key == GLUT_KEY_F7)
        _sX += 0.1;

    if(key == GLUT_KEY_F8)
        _sX -= 0.1;

    if(key == GLUT_KEY_F9)
        _sY += 0.1;
    
    if(key == GLUT_KEY_F10)
        _sY -= 0.1;

    glutPostRedisplay();
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Visualizacao 3D");

    glutDisplayFunc(display);
    glutMouseFunc(GerenciaMouse);
    glutSpecialFunc(Teclado);
    glutReshapeFunc(reshape);


    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glutMainLoop();

    return EXIT_SUCCESS;
}
