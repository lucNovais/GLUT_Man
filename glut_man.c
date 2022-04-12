#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/gl.h>
#include <GL/glut.h>

typedef struct glutman
{
    float pos_x;
    float pos_y;
    float radius;
    float colors[3];
}GlutMan;

typedef struct wall
{
    float pos_x;
    float pos_y;
    float width;
    float height;
    float color[3];
}Wall;

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    
}

void DrawBody(float x, float y, float radius, float colors[]);
void DrawEye(float body_x, float body_y);

void DrawScenario();
void DrawWalls(float x, float y, float width, float height, float color[]);

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    GlutMan glutman = {
        -0.6f,
        0.6f,
        0.1f,
        {0.75f, 0.75f, 0.0f}
    };

    DrawScenario();
    DrawBody(glutman.pos_x, glutman.pos_y, glutman.radius, glutman.colors);
    DrawEye(glutman.pos_x, glutman.pos_y);

    glFlush();
}

void DrawScenario()
{
    Wall leftWall = {
        -1.0f,
        -1.0f,
        0.05f,
        GLUT_WINDOW_HEIGHT,
        {0.6f, 0.6f, 0.6f}
    };

    Wall rightWall = {
        0.95f,
        -1.0f,
        0.05f,
        GLUT_WINDOW_HEIGHT,
        {0.6f, 0.6f, 0.6f}
    };

    Wall topWall = {
        -1.0f,
        0.95f,
        GLUT_WINDOW_WIDTH,
        0.05f,
        {0.6f, 0.6f, 0.6f}
    };

    Wall bottomWall = {
        -1.0f,
        -1.0f,
        GLUT_WINDOW_WIDTH,
        0.05f,
        {0.6f, 0.6f, 0.6f}
    };

    DrawWalls(leftWall.pos_x, leftWall.pos_y, leftWall.width, leftWall.height, leftWall.color);
    DrawWalls(rightWall.pos_x, rightWall.pos_y, rightWall.width, rightWall.height, rightWall.color);
    DrawWalls(topWall.pos_x, topWall.pos_y, topWall.width, topWall.height, topWall.color);
    DrawWalls(bottomWall.pos_x, bottomWall.pos_y, bottomWall.width, bottomWall.height, bottomWall.color);
}

void DrawBody(float init_x, float init_y, float radius, float colors[])
{
    float x, y;
    float t = 0.0f;

    glColor3f(colors[0], colors[1], colors[2]);
    glBegin(GL_POLYGON);
    while(t < 2 * 3.14)
    {
        x = init_x + radius * cos(t);
        y = init_y + radius * sin(t);

        glVertex2f(x, y);
        t += 0.2;
    }

    glEnd();
}

void DrawEye(float body_x, float body_y)
{
    float x, y;
    float t = 0.0f;
    float radius = 0.02f;

    glColor3f(0.2f, 0.2f, 0.6f);
    glBegin(GL_POLYGON);
    while(t < 2 * 3.14)
    {
        x = (body_x + 0.03) + radius * cos(t);
        y = (body_y + 0.05) + radius * sin(t);

        glVertex2f(x, y);
        t += 0.2;
    }

    glEnd();
}

void DrawWalls(float x, float y, float width, float height, float color[])
{
    glBegin(GL_POLYGON);

    glColor3f(color[0], color[0], color[0]); glVertex2f(x, y);
    glColor3f(color[0], color[0], color[0]); glVertex2f(x + width, y);
    glColor3f(color[0], color[0], color[0]); glVertex2f(x, y + height);
    glColor3f(color[0], color[0], color[0]); glVertex2f(x + width, y + height);

    glEnd();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    int s_width = glutGet(GLUT_SCREEN_WIDTH);
    int s_height = glutGet(GLUT_SCREEN_HEIGHT);
    int w_width = 800;
    int w_height = 600;

    glutInitWindowSize(w_width, w_height);
    glutInitWindowPosition((s_width - w_width) / 2, (s_height - w_height) / 2);
    glutCreateWindow("GLUT Man!");

    glutDisplayFunc(Draw);

    init();
    glutMainLoop();

    return 0;
}