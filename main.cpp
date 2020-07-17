#include "Util.h"

int SCREEN_WIDTH = 1080;
int SCREEN_HEIGHT = 720;

// initial canvas color
float *canvasColor = hextoRGB("2F90E6");

// initial camera mode
int CameraMode = NORMAL_MODE;

// set camera speed
const float NormalModeCamSpeed = 5.0f;
const float BirdModeCamSpeed = 10.0f;

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
    glClearColor(canvasColor[0], canvasColor[1], canvasColor[2], 0);
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_COLOR_MATERIAL);
    glLineWidth(3.0f);
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

    /* ============================ GROUND ============================ */

    glColorHex("E5E5E5");
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    /* ============================ HOTEL ============================ */
    {
        // ==============================>> part 1
        {
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

            glColorHex("3A3B35");
            glVertex3f(30.0f, 20.0f, 0.0f);
            glVertex3f(30.0f, 20.0f, -50.0f);
            glVertex3f(-30.0f, 20.0f, -50.0f);
            glVertex3f(-30.0f, 20.0f, 0.0f);
            glEnd();
        }
        
        // ==============================>> part 2
        glColorHex("00FF00");
        //////////////////////////// left
        {
            glBegin(GL_QUADS);
            glVertex3f(-18.0f, 20.0f, -5.0f);
            glVertex3f(-18.0f, 26.0f, -5.0f);
            glVertex3f(-27.0f, 26.0f, -8.0f);
            glVertex3f(-27.0f, 20.0f, -8.0f);

            glVertex3f(-27.0f, 20.0f, -8.0f);
            glVertex3f(-27.0f, 26.0f, -8.0f);
            glVertex3f(-22.0f, 26.0f, -35.0f);
            glVertex3f(-22.0f, 20.0f, -35.0f);

            glVertex3f(-22.0f, 20.0f, -35.0f);
            glVertex3f(-22.0f, 26.0f, -35.0f);
            glVertex3f(-12.2f, 26.0f, -38.0f);
            glVertex3f(-12.2f, 20.0f, -38.0f);

            glVertex3f(-12.2f, 20.0f, -38.0f);
            glVertex3f(-12.2f, 26.0f, -38.0f);
            glVertex3f(-8.1f, 26.0f, -36.3f);
            glVertex3f(-8.1f, 20.0f, -36.3f);

            glVertex3f(-8.1f, 20.0f, -36.3f);
            glVertex3f(-8.1f, 26.0f, -36.3f);
            glVertex3f(-5.0f, 26.0f, -27.0f);
            glVertex3f(-5.0f, 20.0f, -27.0f);

            glVertex3f(-5.0f, 20.0f, -27.0f);
            glVertex3f(-5.0f, 26.0f, -27.0f);
            glVertex3f(-18.0f, 26.0f, -5.0f);
            glVertex3f(-18.0f, 20.0f, -5.0f);
            glEnd();

            glBegin(GL_POLYGON);
            glVertex3f(-17.0f, 26.0f, -2.7f);
            glVertex3f(-29.0f, 26.0f, -6.9f);
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glVertex3f(-12.0f, 26.0f, -40.1f);
            glVertex3f(-6.3f, 26.0f, -37.5f);
            glVertex3f(-2.8f, 26.0f, -27.0f);
            glEnd();
        }
        //////////////////////////// right
        {
            glBegin(GL_QUADS);
            glVertex3f(18.0f, 20.0f, -5.0f);
            glVertex3f(27.0f, 20.0f, -8.0f);
            glVertex3f(27.0f, 26.0f, -8.0f);
            glVertex3f(18.0f, 26.0f, -5.0f);

            glVertex3f(27.0f, 20.0f, -8.0f);
            glVertex3f(26.0f, 20.0f, -40.0f);
            glVertex3f(26.0f, 26.0f, -40.0f);
            glVertex3f(27.0f, 26.0f, -8.0f);

            glVertex3f(26.0f, 20.0f, -40.0f);
            glVertex3f(12.5f, 20.0f, -46.0f);
            glVertex3f(12.5f, 26.0f, -46.0f);
            glVertex3f(26.0f, 26.0f, -40.0f);

            glVertex3f(12.5f, 20.0f, -46.0f);
            glVertex3f(5.0f, 20.0f, -35.0f);
            glVertex3f(5.0f, 26.0f, -35.0f);
            glVertex3f(12.5f, 26.0f, -46.0f);

            glVertex3f(5.0f, 20.0f, -35.0f);
            glVertex3f(18.0f, 20.0f, -5.0f);
            glVertex3f(18.0f, 26.0f, -5.0f);
            glVertex3f(5.0f, 26.0f, -35.0f);
            glEnd();

            glBegin(GL_POLYGON);
            glVertex3f(16.8f, 26.0f, -2.6f);
            glVertex3f(29.1f, 26.0f, -6.7f);
            glVertex3f(28.1f, 26.0f, -41.3f);
            glVertex3f(12.0f, 26.0f, -48.6f);
            glVertex3f(2.6f, 26.0f, -35.0f);
            glEnd();
        }

        // ==============================>> part 3
        glColorHex("3A3B35");
        //////////////////////////// left
        {
            //////////////////// front
            glBegin(GL_POLYGON);
            glVertex3f(-17.0f, 26.0f, -2.7f);
            glVertex3f(-29.0f, 26.0f, -6.9f);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-17.0f, 26.0f, -2.7f);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-17.0f, 86.0f, -2.7f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-17.0f, 86.0f, -2.7f);
            glVertex3f(-26.0f, 86.0f, -8.2f);
            glEnd();
            //////////////////// front right
            glBegin(GL_POLYGON);
            glVertex3f(-2.8f, 26.0f, -27.0f);
            glVertex3f(-17.0f, 26.0f, -2.7f);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-2.8f, 26.0f, -27.0f);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-2.8f, 50.0f, -27.0f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-2.8f, 50.0f, -27.0f);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-2.8f, 86.0f, -27.0f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-2.8f, 86.0f, -27.0f);
            glVertex3f(-17.0f, 86.0f, -2.7f);
            glEnd();
            //////////////////// front left
            glBegin(GL_POLYGON);
            glVertex3f(-29.0f, 26.0f, -6.9f);
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-23.7f, 65.0f, -36.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-23.7f, 65.0f, -36.4f);
            glVertex3f(-23.7f, 86.0f, -36.4f);
            glEnd();
            glBegin(GL_POLYGON);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-23.7f, 86.0f, -36.4f);
            glVertex3f(-26.0f, 86.0f, -8.2f);
            glEnd();
            //////////////////// rear right
            glBegin(GL_QUADS);
            glVertex3f(-6.3f, 26.0f, -37.5f);
            glVertex3f(-6.3f, 86.0f, -37.5f);
            glVertex3f(-2.8f, 86.0f, -27.0f);
            glVertex3f(-2.8f, 26.0f, -27.0f);
            glEnd();
            //////////////////// rear
            glBegin(GL_QUADS);
            glVertex3f(-6.3f, 26.0f, -37.5f);
            glVertex3f(-6.3f, 86.0f, -37.5f);
            glVertex3f(-12.0f, 86.0f, -40.1f);
            glVertex3f(-12.0f, 26.0f, -40.1f);
            glEnd();
            //////////////////// rear left
            glBegin(GL_QUADS);
            glVertex3f(-12.0f, 26.0f, -40.1f);
            glVertex3f(-12.0f, 86.0f, -40.1f);
            glVertex3f(-23.7f, 86.0f, -36.4f);
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glEnd();
            //////////////////// roof
            glBegin(GL_POLYGON);
            glVertex3f(-17.0f, 86.0f, -2.7f);
            glVertex3f(-26.0f, 86.0f, -8.2f);
            glVertex3f(-23.7f, 86.0f, -36.4f);
            glVertex3f(-12.0f, 86.0f, -40.1f);
            glVertex3f(-6.3f, 86.0f, -37.5f);
            glVertex3f(-2.8f, 86.0f, -27.0f);
            glEnd();
        }
        //////////////////////////// right
        {

        }
        // ==============================>> LINES
        glColorHex("FFFFFF");
        glBegin(GL_LINES);
        //////////////////////////// left
        {
            // outside
            glVertex3f(-17.0f, 26.0f, -2.7f);
            glVertex3f(-29.0f, 26.0f, -6.9f);
            glVertex3f(-29.0f, 26.0f, -6.9f);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-26.0f, 86.0f, -8.2f);
            glVertex3f(-17.0f, 86.0f, -2.7f);
            glVertex3f(-26.0f, 86.0f, -8.2f);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-17.0f, 86.0f, -2.7f);
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-17.0f, 26.0f, -2.7f);
            glVertex3f(-29.0f, 26.0f, -6.9f);
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glVertex3f(-23.7f, 86.0f, -36.4f);
            glVertex3f(-23.7f, 86.0f, -36.4f);
            glVertex3f(-26.0f, 86.0f, -8.2f);
            glVertex3f(-2.8f, 86.0f, -27.0f);
            glVertex3f(-17.0f, 86.0f, -2.7f);
            glVertex3f(-2.8f, 86.0f, -27.0f);
            glVertex3f(-2.8f, 26.0f, -27.0f);
            glVertex3f(-2.8f, 26.0f, -27.0f);
            glVertex3f(-6.3f, 26.0f, -37.5f);
            glVertex3f(-6.3f, 26.0f, -37.5f);
            glVertex3f(-6.3f, 86.0f, -37.5f);
            glVertex3f(-6.3f, 86.0f, -37.5f);
            glVertex3f(-2.8f, 86.0f, -27.0f);
            glVertex3f(-6.3f, 26.0f, -37.5f);
            glVertex3f(-12.0f, 26.0f, -40.1f);
            glVertex3f(-12.0f, 26.0f, -40.1f);
            glVertex3f(-12.0f, 86.0f, -40.1f);
            glVertex3f(-12.0f, 86.0f, -40.1f);
            glVertex3f(-6.3f, 86.0f, -37.5f);
            glVertex3f(-12.0f, 26.0f, -40.1f);
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glVertex3f(-12.0f, 86.0f, -40.1f);
            glVertex3f(-23.7f, 86.0f, -36.4f);
            glVertex3f(-2.8f, 26.0f, -27.0f);
            glVertex3f(-17.0f, 26.0f, -2.7f);
            // front left
            glVertex3f(-29.6f, 50.0f, -6.9f); // 1
            glVertex3f(-23.7f, 26.0f, -36.4f);
            glVertex3f(-29.6f, 50.0f, -6.9f); // 2
            glVertex3f(-23.7f, 65.0f, -36.4f);
            glVertex3f(-29.6f, 50.0f, -6.9f); // 3
            glVertex3f(-23.7f, 86.0f, -36.4f);
            // front
            glVertex3f(-17.0f, 26.0f, -2.7f); // 1
            glVertex3f(-29.6f, 50.0f, -6.9f);
            glVertex3f(-29.6f, 50.0f, -6.9f); // 2
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-29.6f, 50.0f, -6.9f); // 3
            glVertex3f(-17.0f, 86.0f, -2.7f);
            // front right
            glVertex3f(-2.8f, 26.0f, -27.0f); // 1
            glVertex3f(-16.6f, 40.0f, -2.75f);
            glVertex3f(-16.6f, 40.0f, -2.75f); // 2
            glVertex3f(-2.8f, 50.0f, -27.0f);
            glVertex3f(-16.6f, 40.0f, -2.75f); // 3
            glVertex3f(-2.8f, 86.0f, -27.0f);
            // rear right
            glVertex3f(-2.8f, 50.0f, -27.0f);
            glVertex3f(-6.3f, 50.0f, -37.5f);
            // rear
            glVertex3f(-6.3f, 50.0f, -37.5f);
            glVertex3f(-12.0f, 50.0f, -40.1f);
            // rear left
            glVertex3f(-12.0f, 50.0f, -40.1f);
            glVertex3f(-23.7f, 65.0f, -36.4f);
        }
        //////////////////////////// right
        {
            // outside
            glVertex3f(16.8f, 26.0f, -2.6f);
            glVertex3f(29.1f, 26.0f, -6.7f);
            glVertex3f(29.1f, 26.0f, -6.7f);
            glVertex3f(28.1f, 26.0f, -41.3f);
            glVertex3f(28.1f, 26.0f, -41.3f);
            glVertex3f(12.0f, 26.0f, -48.6f);
            glVertex3f(12.0f, 26.0f, -48.6f);
            glVertex3f(2.6f, 26.0f, -35.0f);
            glVertex3f(2.6f, 26.0f, -35.0f);
            glVertex3f(16.8f, 26.0f, -2.6f);

            glEnd();
        }
    }
    glutSwapBuffers();
}

float *hextoRGB(std::string hexVal)
{
    int temp;
    float *color = new float[3];

    if (!hexVal.length() == 6)
    {
        std::cout << "Invalid hex color -> '" << hexVal << "'" << std::endl;
        return NULL;
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
                    return NULL;
                }
            }
            color[i] = (float)temp / 255;
        }

        return color;
    }
}

void glColorHex(std::string hexVal)
{
    float *color = hextoRGB(hexVal);
    glColor3f(color[0], color[1], color[2]);
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
    // movement control
    if (CameraMode == NORMAL_MODE)
    {
        switch (key)
        {
        case 'c':
        case 'C':
            CameraMode = BIRD_MODE;
            std::cout << "bird mode camera" << std::endl;

            x = 0.0f;
            y = 50.0f;
            z = 150.0f;
            lx = 0.0f;
            ly = 0.0f;
            lz = -1.0f;
            angleX = 0.0f;
            angleY = 0.0f;
            break;
        case 'W':
        case 'w':
            deltaMove = NormalModeCamSpeed;
            break;
        case 'S':
        case 's':
            deltaMove = -NormalModeCamSpeed;
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
            z = 15.0f;
            lx = 0.0f;
            ly = 0.0f;
            lz = -1.0f;
            angleX = 0.0f;
            angleY = 0.0f;
            break;
        case 'W':
        case 'w':
            deltaMove = BirdModeCamSpeed;
            break;
        case 'S':
        case 's':
            deltaMove = -BirdModeCamSpeed;
            break;
        case 'Q':
        case 'q':
            deltaMoveY = BirdModeCamSpeed;
            break;
        case 'E':
        case 'e':
            deltaMoveY = -BirdModeCamSpeed;
            break;
        }
    }
    if (key == 27) // Esc
        exit(EXIT_SUCCESS);
    if (key == ' ')
    {
        if (isLighted)
        {
            glClearColor(canvasColor[0], canvasColor[1], canvasColor[2], 0);
            glDisable(GL_LIGHTING);
            glDisable(GL_LIGHT7);
            isLighted = 0;
        }
        else
        {
            glClearColor(0.0, 0.0, 0.0, 0.0);
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT7);
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
