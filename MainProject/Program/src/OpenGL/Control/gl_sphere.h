
#ifndef GRAPHICSTEST_GL_SPHERE_H
#define GRAPHICSTEST_GL_SPHERE_H

#include "../gl_mesh.h"
#include "../gl_main_manager.h"
#include "../Figures/field_generator.h"

struct gl_sphere_parameters {
    float x_center;
    float y_center;
    float z_center;
    float radius;
    float stackCount;
    float sectorCount;

    int     activateNormals;
    int    activateTexture;

    size_t offsetVertexPosition;
    size_t offsetNormalPosition;
    size_t offsetTexturePosition;
    size_t offsetVertex;

    char* image_rgb;
    size_t width;
    size_t height;
    char indexVertex;
    char indexNormal;
    char indexTexture;
};
struct gl_sphere {
    struct gl_mesh mesh_sphere;
    size_t offset_init_queue;
};
void gl_sphere_init(struct gl_main_manager* manager, struct gl_sphere* sphere, struct gl_sphere_parameters* parameters);
void gl_sphere_free(struct gl_main_manager* manager, struct gl_sphere* sphere);
void gl_sphere_synchronize(struct gl_main_manager* manager, struct gl_sphere* sphere);
#endif //GRAPHICSTEST_GL_SPHERE_H