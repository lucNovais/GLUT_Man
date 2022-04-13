//Lucas Novais - 18.1.8046
//Thiago Figueiredo - 18.1.8017

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
    float speed;
    // If facing = 0, the character is facing right;
    // If facing = 1, the character is facing left;
    int facing;
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

GlutMan glutman = {
    -0.65f,
    0.65f,
    0.1f,
    0.015f,
    0,
    {0.75f, 0.75f, 0.0f}
};

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    
}

void DrawBody(float x, float y, float radius, float colors[]);
void DrawEye(float body_x, float body_y, int facing);
void DrawMouth(float body_x, float body_y, int facing);
void DrawScenario();
void DrawWalls(float x, float y, float width, float height, float color[]);

void Move(int key, int x, int y)
{
    if(key == GLUT_KEY_UP && (glutman.pos_y + glutman.speed) < 1 - glutman.radius - 0.05f)
    {
        glutman.pos_y += glutman.speed;
        glutman.facing = 3;
        glutPostRedisplay();
    }
    if(key == GLUT_KEY_DOWN  && (glutman.pos_y - glutman.speed) > (-1 + glutman.radius + 0.05f))
    {
        glutman.pos_y -= glutman.speed;
        glutman.facing = 2;
        glutPostRedisplay();
    }
    if(key == GLUT_KEY_LEFT && (glutman.pos_x - glutman.speed) > (-1 + glutman.radius + 0.05f))
    {
        glutman.pos_x -= glutman.speed;
        glutman.facing = 1;
        glutPostRedisplay();
    }
    if(key == GLUT_KEY_RIGHT && (glutman.pos_x + glutman.speed) < 1 - glutman.radius - 0.05f)
    {
        glutman.pos_x += glutman.speed;
        glutman.facing = 0;
        glutPostRedisplay();
    }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    DrawScenario();
    DrawBody(glutman.pos_x, glutman.pos_y, glutman.radius, glutman.colors);
    DrawEye(glutman.pos_x, glutman.pos_y, glutman.facing);
    DrawMouth(glutman.pos_x, glutman.pos_y, glutman.facing);

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

void DrawEye(float body_x, float body_y, int facing)
{
    float x, y;
    float t = 0.0f;
    float radius = 0.015f;

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    while(t < 2 * 3.14)
    {
        if(facing == 0)
        {
            x = (body_x + 0.03) + radius * cos(t);
            y = (body_y + 0.05) + radius * sin(t);
        }
        else if(facing == 1)
        {
            x = (body_x - 0.03) + radius * cos(t);
            y = (body_y + 0.05) + radius * sin(t);
        
        }
        else if(facing == 2)
        {
            x = (body_x + 0.05) + radius * cos(t);
            y = (body_y - 0.03) + radius * sin(t);
        }
        else if(facing == 3)
        {
            x = (body_x - 0.05) + radius * cos(t);
            y = (body_y + 0.03) + radius * sin(t);
        }
        
        glVertex2f(x, y);
        t += 0.2;
    }

    glEnd();
}

void DrawMouth(float body_x, float body_y, int facing)
{
    glBegin(GL_POLYGON);

    glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x, body_y);

    if(facing == 0)
    {
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x + 0.1f, body_y + 0.03f);
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x + 0.1f, body_y - 0.035f);
    }
    else if(facing == 1)
    {
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x - 0.1f, body_y + 0.03f);
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x - 0.1f, body_y - 0.035f);
    }
    else if(facing == 2)
    {
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x - 0.03f, body_y - 0.1f);
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x + 0.035f, body_y - 0.1f);
    }
    else if(facing == 3)
    {
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x - 0.03f, body_y + 0.1f);
        glColor3f(0.0f, 0.0f, 0.0f); glVertex2f(body_x + 0.035f, body_y + 0.1f);
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
    glutSpecialFunc(Move);

    init();
    glutMainLoop();

    return 0;
}