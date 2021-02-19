#include <math.h>

#include <GLFW/glfw3.h>
#include "lib/glm/matrix.hpp"
#include "lib/glm/vector_relational.hpp"

#define PI 3.14159265

glm::dmat2x2 rotation_matrix(int theta) {
    /*
     * [ cos() -sin()
     *   sin() cos()  ]
     */
    double r = theta*PI/180;
    return glm::dmat2x2(cos(r), -sin(r),
                        sin(r),  cos(r));
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize variables to be used in the loop */

    int ROTATION_FACTOR = 5;  // degrees to rotate per frame

    // matrix for rotation
    glm::dmat2x2 rotm = rotation_matrix(ROTATION_FACTOR);
    // vectors for triangle
    glm::dvec2 v1 = glm::dvec2(-0.5f, -0.5f);
    glm::dvec2 v2 = glm::dvec2( 0.0f,  0.5f);
    glm::dvec2 v3 = glm::dvec2( 0.5f, -0.5f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Apply rotation to triangle vertices */
        v1 = rotm * v1;
        v2 = rotm * v2;
        v3 = rotm * v3;

        /* Draw a triangle */
        glBegin(GL_TRIANGLES);
        glVertex2f(v1[0], v1[1]);
        glVertex2f(v2[0], v2[1]);
        glVertex2f(v3[0], v3[1]);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
