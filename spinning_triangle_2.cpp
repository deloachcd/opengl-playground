#include <stdio.h>
#include <math.h>

#include <iostream>

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
    float r = theta*PI/180;
    return glm::dmat2x2(cos(r), -sin(r),
                        sin(r),  cos(r));
}

static unsigned int CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "
            << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader, FUCK!" << std::endl;
        std::cout << message << std::endl;
    }
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader,
        const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void push_vec2(glm::vec2* arr_vectors, float buffer[], unsigned n_vec2) {
    for (unsigned i = 0; i < n_vec2; i++) {
        buffer[i*2] = arr_vectors[i][0];
        buffer[(i*2)+1] = arr_vectors[i][1];
    }
}

int spin_triangle() {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Need this to enable GLSL 3.3 core */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    } else {
        printf("%s\n", glGetString(GL_VERSION));
    }

    /* Initialize variables to be used in the loop */

    int ROTATION_FACTOR = 5;  // degrees to rotate per frame

    // matrices for rotation
    glm::dmat2x2 rotm_clock = rotation_matrix(ROTATION_FACTOR);

    // vectors for triangle
    glm::vec2 vectors[] = {
        glm::vec2(-0.5f, -0.5f),
        glm::vec2( 0.0f,  0.5f),
        glm::vec2( 0.5f, -0.5f)
    };

    // buffer for vector positions
    float vposition[sizeof(float)*6];
    push_vec2(vectors, vposition, sizeof(vectors)/sizeof(glm::vec2));

    unsigned int vertexArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, vposition, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);

    std::string vShader = R"EOF(
    #version 330 core
    layout(location = 0) in vec4 position;
    void main() {
        gl_Position = position;
    }
    )EOF";
    std::string fShader = R"EOF(
    #version 330 core
    layout(location = 0) out vec4 color;
    void main() {
        color = vec4(0.0, 1.0, 1.0, 1.0);
    }
    )EOF";
    unsigned int shader = CreateShader(vShader, fShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw triangle from buffer */
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
