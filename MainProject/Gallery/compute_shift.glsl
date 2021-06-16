R"(
#version 430 compatibility
#extension GL_ARB_compute_shader : enable
#extension GL_ARB_shader_storage_buffer_object : require

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

uniform shader_data
{
    uniform vec3 shift;
};

struct mesh_data{
    vec3 position;
    int  colors;
    vec2 texCoord;
};
layout(std430, binding = 1) buffer inputData
{
    mesh_data read_buffer[];
};
layout(std430, binding = 2) buffer outputData
{
    mesh_data write_buffer[];
};
void main(){
    uint idx = (gl_WorkGroupID.x * gl_WorkGroupSize.x + gl_LocalInvocationID.x);
    uint idy = (gl_WorkGroupID.y * gl_WorkGroupSize.y + gl_LocalInvocationID.y);
    uint stride_y = (gl_NumWorkGroups.y * gl_WorkGroupSize.y);
    uint stride_x = (gl_NumWorkGroups.x * gl_WorkGroupSize.x);
    vec3 position = read_buffer[idy * stride_x + idx].position;
    write_buffer[idy * stride_x + idx].position = position + shift;
}

)"