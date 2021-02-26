#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/matrix.hpp>
#include <glm/vector_relational.hpp>

#define PI 3.14159265

glm::mat3x3 rot3d_matrix(int theta, char axis) {
    double r = theta*PI/180;
    if (axis == 'x') {
        return glm::mat3x3(1,      0,       0,
                           0, cos(r), -sin(r),
                           0, sin(r),  cos(r));
    } else if (axis == 'y') {
        return glm::mat3x3( cos(r),  0,  sin(r),
                                 0,  1,       0,
                           -sin(r),  0,  cos(r));
    } else if (axis == 'z') {
        return glm::mat3x3(cos(r), -sin(r), 1,
                           sin(r),  cos(r), 0,
                                0,       0, 1);
    }
}

glm::vec3 UNIT_I3D = glm::vec3(1, 0, 0);
glm::vec3 UNIT_J3D = glm::vec3(0, 1, 0);
glm::vec3 UNIT_K3D = glm::vec3(0, 0, 1);

glm::vec3 BUCEPHALUS_VECTORS[] = {
    UNIT_I3D,
    UNIT_J3D,
    UNIT_K3D,
    UNIT_I3D * -1.0f,
    UNIT_J3D * -1.0f,
    UNIT_K3D * -1.0f,
    rot3d_matrix( 45, 'x') * rot3d_matrix( 45, 'y') * UNIT_K3D,
    rot3d_matrix(-45, 'x') * rot3d_matrix( 45, 'y') * UNIT_K3D,
    rot3d_matrix( 45, 'y') * rot3d_matrix( 45, 'z') * UNIT_I3D,
    rot3d_matrix( 45, 'y') * rot3d_matrix(-45, 'z') * UNIT_I3D,
    rot3d_matrix( 45, 'x') * rot3d_matrix( 45, 'y') * UNIT_K3D * -1.0f,
    rot3d_matrix(-45, 'x') * rot3d_matrix( 45, 'y') * UNIT_K3D * -1.0f,
    rot3d_matrix( 45, 'y') * rot3d_matrix( 45, 'z') * UNIT_I3D * -1.0f,
    rot3d_matrix( 45, 'y') * rot3d_matrix(-45, 'z') * UNIT_I3D * -1.0f,
};
