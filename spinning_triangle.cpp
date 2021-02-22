#include <stdio.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>
#include <glm/vector_relational.hpp>

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

int spin_triangle() {
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

    /* Sanity check for GLEW */
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        printf("OH NO INDEPENDENCE DAY\n");
    }

    /* Initialize variables to be used in the loop */

    int ROTATION_FACTOR = 5;  // degrees to rotate per frame

    // matrices for rotation
    glm::dmat2x2 rotm_clock = rotation_matrix(ROTATION_FACTOR);
    glm::dmat2x2 rotm_counter = glm::inverse(rotm_clock);

    // vectors for triangle 1
    glm::dvec2 t1v1 = glm::dvec2(-0.5f, -0.5f);
    glm::dvec2 t1v2 = glm::dvec2( 0.0f,  0.5f);
    glm::dvec2 t1v3 = glm::dvec2( 0.5f, -0.5f);
    glm::dvec2 t2v3 = glm::dvec2(-0.5f, -0.5f);
    glm::dvec2 t2v2 = glm::dvec2( 0.0f,  0.5f);
    glm::dvec2 t2v1 = glm::dvec2( 0.5f, -0.5f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Apply rotation to triangle vertices */
        t1v1 = rotm_clock * t1v1;
        t1v2 = rotm_clock * t1v2;
        t1v3 = rotm_clock * t1v3;
        t2v1 = rotm_counter * t2v1;
        t2v2 = rotm_counter * t2v2;
        t2v3 = rotm_counter * t2v3;

        /* Draw the triangles */
        glBegin(GL_TRIANGLES);
        glVertex2f(t1v1[0], t1v1[1]);
        glVertex2f(t1v2[0], t1v2[1]);
        glVertex2f(t1v3[0], t1v3[1]);
        glEnd();
        glBegin(GL_TRIANGLES);
        glVertex2f(t2v1[0], t2v1[1]);
        glVertex2f(t2v2[0], t2v2[1]);
        glVertex2f(t2v3[0], t2v3[1]);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
