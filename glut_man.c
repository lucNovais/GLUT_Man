//Lucas Novais - 18.1.8046
//Thiago Figueiredo - 18.1.8017

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <GL/gl.h>
#include <GL/glut.h>

typedef struct glutman
{
    float pos_x;
    float pos_y;
    float radius;
    float speed;
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

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void DrawBody(float x, float y, float radius, float colors[]);
void DrawEye(float body_x, float body_y, int facing);
void DrawMouth(float body_x, float body_y, int facing);
void DrawScenario();
void DrawWalls(float x, float y, float width, float height, float color[]);
void DrawFood(float pos_x, float pos_y, float radius);
void GenerateFoodPosition(float* food_positions, int food_number);

GlutMan glutman = {
    -0.65f,
    0.65f,
    0.1f,
    0.018f,
    0,
    {0.75f, 0.75f, 0.0f}
};

void Move(int key, int x, int y)
{
    if(key == GLUT_KEY_UP && (glutman.pos_y + glutman.speed) < 1 - glutman.radius - 0.05f)
    {
        glutman.pos_y += glutman.speed;
        glutman.facing = 3;
        glutPostRedisplay();

        // glTranslatef(glutman.pos_x, glutman.pos_y + glutman.speed, 0.0f);
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

void GenerateFoodPosition(float* food_positions, int food_number)
{
    float positions_x[food_number];
    float positions_y[food_number];
    float a = 2.0f;

    float food_x = ((float)rand() / (float)(RAND_MAX)) / a;
    float food_y = ((float)rand() / (float)(RAND_MAX)) / a;

    for(int i = 0; i <= food_number; i++)
    {
        if(food_x > 0.95f || food_x < 0.05)
        {
            while(food_x > 0.95f || food_x < 0.05)
                food_x = ((float)rand() / (float)(RAND_MAX)) / a;
            positions_x[i] = food_x;
        }

        if(food_y > 0.95f || food_y < 0.05)
        {
            while(food_y > 0.95f || food_y < 0.05)
                food_y = ((float)rand() / (float)(RAND_MAX)) / a;
            positions_y[i] = food_y;
        }
    }

    memcpy(food_positions, positions_x, food_number * sizeof(float));
    memcpy(food_positions, positions_y, food_number * sizeof(float));
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

void DrawFood(float pos_x, float pos_y, float radius)
{
    float x, y;
    float t = 0.0f;

    glColor3f(0.8f, 0.0f, 0.2f);
    glBegin(GL_POLYGON);

    while(t < 2 * 3.14)
    {
        x = pos_x + radius * cos(t);
        y = pos_y + radius * sin(t);

        glVertex2f(x, y);
        t += 0.2;
    }

    glEnd();
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    glutInit(&argc, argv);

    int s_width = glutGet(GLUT_SCREEN_WIDTH);
    int s_height = glutGet(GLUT_SCREEN_HEIGHT);
    int w_width = 800;
    int w_height = 600;

    float* food_positions = malloc(8 * sizeof(float));
    GenerateFoodPosition(&food_positions, 8);

    for(int i = 0; i < 8; i++)
    {
        printf("%f", food_positions[i]);
    }

    glutInitWindowSize(w_width, w_height);
    glutInitWindowPosition((s_width - w_width) / 2, (s_height - w_height) / 2);
    glutCreateWindow("GLUT Man!");

    glutDisplayFunc(Draw);
    glutSpecialFunc(Move);

    init();
    glutMainLoop();

    return 0;
}
