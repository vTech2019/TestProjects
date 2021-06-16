R"(
#version 430 compatibility
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_image_load_store : enable
#define M_PI 3.1415926535

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;
uniform float mu;
layout (binding = 0, rgba8) readonly uniform image2D   img_input;
layout (binding = 1, rgba8) writeonly uniform image2D  img_output;

float gauss_distribution(float x,float mu,float s){
    float p1 = -0.5f * pow((x - mu)/s, 2);
    float p2 = (s * sqrt(2*M_PI));
    return exp(p1)/ p2;
}
float gauss_distribution_xy(float x, float y,float mu_x, float mu_y,float s){
    return gauss_distribution(x, mu_x, s) * gauss_distribution(y, mu_y, s);
}

void main(){
    float idx = float(gl_WorkGroupID.x * gl_WorkGroupSize.x + gl_LocalInvocationID.x);
    float idy = float(gl_WorkGroupID.y * gl_WorkGroupSize.y + gl_LocalInvocationID.y);
    float stride_y = float(gl_NumWorkGroups.y * gl_WorkGroupSize.y);
    float stride_x = float(gl_NumWorkGroups.x * gl_WorkGroupSize.x);
    ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
    float x_center = imageSize(img_input).x / 2;
    float y_center = imageSize(img_input).y / 2;

    imageStore(img_output, storePos, vec4(255000*gauss_distribution_xy(idx, idy, x_center, y_center, 100), 0.0, 0.0, 1.0));
}

)"