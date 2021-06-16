#version 430

layout ( location = 0) in vec3 vertex_position;
layout ( location = 1) in vec3 vertex_normal_coord;
layout ( location = 2) in vec2 vertex_texture_coord;

uniform BLOCK
{
    uvec4  mouse;
    mat4  MODELVIEW;
    mat4  MODEL;
    mat4  VIEW;
};


out vec4 fragment_color;
out vec2 fragment_texture_coord;

out flat uvec2 fragment_mouse_coord;

void main() {

    fragment_mouse_coord = mouse.xy;
    fragment_texture_coord = vertex_texture_coord;

    gl_Position = (MODELVIEW *  VIEW * MODEL * vec4(vertex_position, 1));
}
