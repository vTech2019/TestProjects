//
// Created by human on 04.04.2020.
//

#ifndef GRAPHICSTEST_GL_MESH_H
#define GRAPHICSTEST_GL_MESH_H
#include "../MainEvents/main_queue.h"
#include "gl_header.h"
#include <stddef.h>

struct gl_mesh_parameters {
    size_t offsetVertexPosition;
    size_t offsetColorPosition;
    size_t offsetNormalPosition;
    size_t offsetTexturePosition;
    size_t offsetVertex;

    int             numberPositions;
    int             activateColors;
    int             activateNormals;
    int             activateTexture;

    char                indexProgramPosition;
    char                indexProgramColor;
    char                indexProgramNormal;
    char                indexProgramTexture;

    void*               return_memory;
    float*              return_vertices;
    unsigned int*       return_indices;
    size_t              return_number_vertices;
    size_t              return_number_indices;

    char*               image_rgb;
    size_t              width, height;
};

struct gl_mesh {
        GLsizei         m_vertexCount;
        GLsizei         m_indexCount;
        GLuint          m_VAO;
        GLuint          m_textureId;
        GLuint          m_vertexBuffer;
        GLuint          m_indexBuffer;
};
void gl_mesh_create2DTexture_RGB8_thread(struct gl_mesh* mesh, const GLbyte* image, GLuint width, GLuint height);
void gl_mesh_init_thread(struct gl_mesh_parameters* vertex_data, struct gl_mesh* mesh);
void gl_mesh_free_thread(struct gl_mesh* mesh);
void gl_mesh_init_draw(struct gl_mesh* mesh, struct main_queue* gl_draw_command_queue);
#endif //GRAPHICSTEST_GL_MESH_H
