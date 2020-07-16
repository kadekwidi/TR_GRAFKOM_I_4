#include "Util.h"

int CameraMode = NORMAL_MODE;

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

// angle of rotation for the camera direction
float angleX = 0.0f;
float angleY = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = -1.0f;

// XZ initial position of the camera
float x = 0.0f;
float y = 1.0f;
float z = 10.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
float deltaMove = 0.0f;
float deltaMoveY = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

int isLighted = 0;

int main(int argc, char **argv)
{
    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    glutCreateWindow("Rixos Premium Dubai JBR");
    init();

    // register callbacks
    glutDisplayFunc(renderObjects);
    glutReshapeFunc(resizeWindow);
    glutIdleFunc(renderObjects);

    // camera control
    glutKeyboardFunc(pressKey);
    glutIgnoreKeyRepeat(1);
    glutKeyboardUpFunc(releaseKey);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    // enter GLUT event processing cycle
    glutMainLoop();

    return EXIT_SUCCESS;
}

void init(void)
{
    glClearColor(0.184f, 0.564f, 0.901f, 0);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_COLOR_MATERIAL);
    glMatrixMode(GL_MODELVIEW);
}

void renderObjects(void)
{
    if (deltaMove || deltaMoveY)
        computeCameraPos(deltaMove, deltaMoveY);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt(x, y, z,
              x + lx, y + ly, z + lz,
              0.0f, 1.0f, 0.0f);

    // Draw ground

    glColorHex("E5E5E5");
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    // bottom
    glColorHex("2B2D57");
    glBegin(GL_QUADS);
    glVertex3f(30.0f, 0.0f, 0.0f);
    glVertex3f(-30.0f, 0.0f, 0.0f);
    glVertex3f(-30.0f, 20.0f, 0.0f);
    glVertex3f(30.0f, 20.0f, 0.0f);

    glVertex3f(30.0f, 0.0f, 0.0f);
    glVertex3f(30.0f, 0.0f, -50.0f);
    glVertex3f(30.0f, 20.0f, -50.0f);
    glVertex3f(30.0f, 20.0f, 0.0f);

    glVertex3f(30.0f, 0.0f, -50.0f);
    glVertex3f(-30.0f, 0.0f, -50.0f);
    glVertex3f(-30.0f, 20.0f, -50.0f);
    glVertex3f(30.0f, 20.0f, -50.0f);

    glVertex3f(-30.0f, 0.0f, 0.0f);
    glVertex3f(-30.0f, 0.0f, -50.0f);
    glVertex3f(-30.0f, 20.0f, -50.0f);
    glVertex3f(-30.0f, 20.0f, 0.0f);


    glVertex3f(30.0f, 20.0f, 0.0f);
    glVertex3f(30.0f, 20.0f, -50.0f);
    glVertex3f(-30.0f, 20.0f, -50.0f);
    glVertex3f(-30.0f, 20.0f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

void glColorHex(std::string hexVal)
{
    int temp;
    float color[3];

    if (!hexVal.length() == 6)
    {
        std::cout << "Invalid hex color -> '" << hexVal << "'" << std::endl;
        return;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            temp = 0;
            for (int j = 0; j < 2; j++)
            {
                if (hexVal[(i * 2) + j] >= '0' && hexVal[(i * 2) + j] <= '9')
                {
                    temp += (hexVal[(i * 2) + j] - 48) * (pow(16, 1 - j));
                }
                else if (hexVal[(i * 2) + j] >= 'A' && hexVal[(i * 2) + j] <= 'F')
                {
                    temp += (hexVal[(i * 2) + j] - 55) * (pow(16, 1 - j));
                }
                else
                {
                    std::cout << "Invalid hex color -> '" << hexVal << "'" << std::endl;
                    return;
                }
            }
            color[i] = (float)temp / 255;
        }
        glColor3f(color[0], color[1], color[2]);
    }
}

void resizeWindow(int w, int h)
{
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 1000.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void computeCameraPos(float dm, float dmy)
{
    x += dm * lx * 0.1f;
    y += dmy * 0.1f;
    z += dm * lz * 0.1f;
    printf("x=%.2f, y=%.2f, z=%.2f\tlx=%.2f, ly=%.2f, lz=%.2f\n", x, y, z, lx, ly, lz);
}

void pressKey(unsigned char key, int xx, int yy)
{
    std::cout << key << std::endl;
    if (CameraMode == NORMAL_MODE)
    {
        switch (key)
        {
        case 'c':
        case 'C':
            CameraMode = BIRD_MODE;
            std::cout << "bird mode camera" << std::endl;

            x = 0.0f;
            y = 10.0f;
            z = 30.0f;
            lx = 0.0f;
            ly = 0.0f;
            lz = -1.0f;
            angleX = 0.0f;
            angleY = 0.0f;
            break;
        case 'W':
        case 'w':
            deltaMove = 5.0f;
            break;
        case 'S':
        case 's':
            deltaMove = -5.0f;
            break;
        }
    }
    else
    {
        switch (key)
        {
        case 'c':
        case 'C':
            CameraMode = NORMAL_MODE;
            std::cout << "normal mode camera" << std::endl;

            x = 0.0f;
            y = 1.0f;
            z = 5.0f;
            lx = 0.0f;
            ly = 0.0f;
            lz = -1.0f;
            angleX = 0.0f;
            angleY = 0.0f;
            break;
        case 'W':
        case 'w':
            deltaMove = 10.0f;
            break;
        case 'S':
        case 's':
            deltaMove = -10.0f;
            break;
        case 'Q':
        case 'q':
            deltaMoveY = 10.0f;
            break;
        case 'E':
        case 'e':
            deltaMoveY = -10.0f;
            break;
        }
    }
    if (key == 27)
        exit(EXIT_SUCCESS);
    if (key == ' ')
    {
        if (isLighted)
        {
            glClearColor(0.184f, 0.564f, 0.901f, 0);
            glDisable(GL_LIGHTING);
            isLighted = 0;
        }
        else
        {
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glEnable(GL_LIGHTING);
            isLighted = 1;
        }
    }
}

void releaseKey(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'W':
    case 'w':
    case 'S':
    case 's':
        deltaMove = 0;
        break;
    case 'Q':
    case 'q':
    case 'E':
    case 'e':
        deltaMoveY = 0;
        break;
    }
}

void mouseMove(int x, int y)
{
    // this will only be true when the left button is down
    if (xOrigin >= 0)
    {

        // update deltaAngleX
        deltaAngleX = (x - xOrigin) * 0.001f;
        deltaAngleY = (y - yOrigin) * 0.001f;

        // update camera's direction
        lx = sin(angleX + deltaAngleX);
        lz = -cos(angleX + deltaAngleX);
        ly = tan(angleY + deltaAngleY);
    }
}

void mouseButton(int button, int state, int x, int y)
{

    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON)
    {

        // when the button is released
        if (state == GLUT_UP)
        {
            angleX += deltaAngleX;
            angleY += deltaAngleY;
            xOrigin = -1;
            yOrigin = -1;
        }
        else
        { // state = GLUT_DOWN
            xOrigin = x;
            yOrigin = y;
        }
    }
}
