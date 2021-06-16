//
// Created by human on 2/4/20.
//
#ifndef LAB_4_GLGALLERY_H
#define LAB_4_GLGALLERY_H

#include "../OpenGL/MainMenu/glMainMenu.h"
#include "../OpenGL/glMesh.h"
#include "../OpenGL/glProgram.h"
#include "../Figures/FieldGenerator.h"
#include "ppm_reader.h"
#include "../Matrix/Matrix4x4.h"
#include "../OpenGL/Control/Button/glButton.h"

class glGallery : protected glMainManager, protected glMainMenu{
    static void Mouse(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0);
    static void Render(void* data_0, void* data_1, void* data_2, void* data_3 );
    static void Resize(size_t width, size_t height, void* data_0, void* data_1 );
    GLfloat shiftButtonX;
    GLfloat shiftButtonY;
    glButton mainButton;
    glButtonProgram mainButtonProgram;
    glProgram GalleryDrawProgram;

    std::vector<glMesh> meshView;
    GLuint mouseData[4]{};
    fMatrix4x4 viewMatrix;

    void initDrawView(float x, float y, float z, float width, float height);
public:
    glGallery();
    ~glGallery();
};



#endif //LAB_4_GLGALLERY_H
