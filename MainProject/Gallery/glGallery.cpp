//
// Created by human on 2/4/20.
//

#include "glGallery.h"
#include "../Images/LoadImages.h"

#define SPEED_SHIFT 0.05
const char* vertexFragmentShader[] = {
#include "vertex.glsl"
        ,
#include "pixel.glsl"
};
unsigned int drawShaders[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER};

void glGallery::Mouse(size_t x, size_t y, unsigned char mouseKeyCode, void* data_0){
    glGallery* ptr = (glGallery*)data_0;
    if ((unsigned char)mouseKeyCode::LeftKey == mouseKeyCode){
        ptr->mouseData[2] = mouseKeyCode;
        ptr->mouseData[3] ^= 1;
    }else if((unsigned char)mouseKeyCode::UpWheel == mouseKeyCode){
        ptr->viewMatrix.value[0].s[0] = ptr->viewMatrix.value[0].s[0] * 0.9;
        ptr->viewMatrix.value[1].s[1] = ptr->viewMatrix.value[1].s[1] * 0.9;
        ptr->viewMatrix.value[3].s[0] *= 0.9;
        ptr->viewMatrix.value[3].s[1] *= 0.9;
    }else if((unsigned char)mouseKeyCode::DownWheel == mouseKeyCode){
        ptr->viewMatrix.value[0].s[0] *= 1.1;
        ptr->viewMatrix.value[1].s[1] *= 1.1;
        ptr->viewMatrix.value[3].s[0] *= 1.1;
        ptr->viewMatrix.value[3].s[1] *= 1.1;
    }else
    if (ptr->mouseData[3] ){
        GLfloat directionX =  ptr->shiftButtonX - (float)x ;
        GLfloat directionY =  ptr->shiftButtonY - (float)y ;
        GLfloat norm = sqrt(directionX * directionX + directionY*directionY + 1);
        ptr->viewMatrix.value[3].s[0] += (directionX / norm) * SPEED_SHIFT;;
        ptr->viewMatrix.value[3].s[1] += (directionY / norm) * SPEED_SHIFT;
        ptr->shiftButtonX = x ;
        ptr->shiftButtonY = y ;
    }
    ptr->GalleryDrawProgram.updateUniform(ptr->viewMatrix.value, 0,1, sizeof(ptr->viewMatrix));
    ptr->GalleryDrawProgram.updateUniform(ptr->mouseData, 0,0, sizeof(ptr->mouseData));

    ptr->mouseData[0] = x;
    ptr->mouseData[1] = y;
}
void glGallery::Render(void* data_0, void* data_1, void* data_2, void* data_3 ){
    auto* ptr = (glGallery*)data_0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(1,1,1,1);
    ptr->GalleryDrawProgram.useProgram();
    for (size_t i  = 0; i < ptr->meshView.size();i++)
        ptr->meshView[i].draw();
    ptr->mainMenuProgram.useProgram();
    ptr->mainMenuMesh.draw();
    ptr->mainButtonProgram.program.useProgram();
    ptr->mainButton.mesh.draw();
}
void glGallery::Resize(size_t width, size_t height, void* data_0, void* data_1 ){
    glGallery* ptr = (glGallery*)data_0;
    glViewport(0, 0, width, height);
    glOrtho(&ptr->viewMatrix.value[0].s0, 0,  (float)width , 0, (float)height, 10, -10);

    ptr->initMainMenuMesh(2, 0.1);
    ptr->GalleryDrawProgram.updateUniform(ptr->viewMatrix.value, 0,1, sizeof(viewMatrix));
}
void* reallocator(void** memory, size_t width, size_t height, size_t numberBitPixel){
    *memory = (void*)realloc(*memory, width * height * numberBitPixel / 8 + sizeof(imageMatrix));
    imageMatrix* ptr = static_cast<imageMatrix *>(*memory);
    ptr->height = height;
    ptr->width = width;
    ptr->numberBytePixel = numberBitPixel / 8;
    return ptr->data;
}
void glGallery::initDrawView(float x, float y, float z, float width, float height){
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    LoadImages images;
    imagesMatrix* dataImages = images.load("/media/human/2A520E98520E68C1/Images/lab8");
    meshView.resize(dataImages->numberImages);
    size_t h_images = sqrt(dataImages->numberImages);
    h_images += (dataImages->numberImages % h_images) ? 1 : 0;
    size_t w_images = dataImages->numberImages / h_images;
    w_images += (dataImages->numberImages % w_images) ? 1 : 0;
    float step_y = height / h_images;
    float step_x = width / w_images;

    float start_y = y - height / 2;
    float start_x = x - width / 2;
    FieldParameters parameters;
    MeshParameters meshParameters;
    char* nameVertexAttrib[] {"position", "vertex_texture_coord"};
    GLint vertexIndices[2];
    for (size_t i = 0, index = 0; i < h_images; i++){
        for (size_t j = 0; j < w_images; j++, index++){
            if (index < dataImages->numberImages){
                parameters.numberPositions = FieldParametersPosition::xyz;
                parameters.activateColors = FieldParametersColors::nothing;
                parameters.activateTexture = FieldParametersTextures::activate;
                parameters.offsetVertexPosition = 0;
                parameters.offsetColorPosition = 0;
                parameters.offsetTexturePosition = 3;
                parameters.offsetVertex = 5;
                parameters.xyz_near[0] = start_x + j * step_x;
                parameters.xyz_near[1] = start_y + i * step_y;
                parameters.xyz_near[2] = 0;
                parameters.xyz_step[0] = step_x;
                parameters.xyz_step[1] = step_y;
                parameters.xyz_step[2] = 0;
                parameters.number_x = 2;
                parameters.number_y = 2;
                GalleryDrawProgram.getAttribs(nameVertexAttrib, vertexIndices,2 );
                meshParameters.offsetVertexPosition = 0;
                meshParameters.offsetTexturePosition = 12;
                meshParameters.offsetColorPosition = 0;
                meshParameters.activateTexture = (size_t)parameters.activateTexture;
                meshParameters.activateColors = (size_t)parameters.activateColors;
                meshParameters.numberPositions = (size_t)parameters.numberPositions;
                meshParameters.indexPosition = vertexIndices[0];
                meshParameters.indexTexture = vertexIndices[1];
                meshParameters.indexColor = 0;
                FieldGenerate(parameters, vertices, indices);
                meshView[index].init(meshParameters, vertices, indices);
                meshView[index].create2DTexture_RGB8(reinterpret_cast<GLbyte *>(dataImages->images[index]->data), dataImages->images[index]->width, dataImages->images[index]->height);
            }
        }
    }

}
glGallery::glGallery() : GalleryDrawProgram(drawShaders, vertexFragmentShader, 2)
                         {
  //  mainButtonProgram.init();
    mainButton.init(0, 0, 0, 1, 1, 1280, 720, mainButtonProgram);
    shiftButtonX = 0.0;
    shiftButtonY = 0.0;
    setCallbackRender(Render, this, nullptr, nullptr, nullptr);
    setCallbackMouse(Mouse, this);
    setCallbackResizeWindow(Resize, this, nullptr);

    //initDrawView(360,360,0,720,720);
    dispatch();
}

glGallery::~glGallery() {
}
