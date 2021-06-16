#version 110

attribute vec2 vertex_position;
attribute vec2 vertex_texture_coord;

uniform mat4  MVP;
uniform vec4  mouse;
uniform vec2  windowSize;
uniform vec2  time_SpeedAnimation;

varying vec4 fragment_color;
varying vec2 fragment_texture_coord;
varying vec4 fragment_mouse_data;
varying vec2 fragment_window_size;
varying vec2 fragment_time_SpeedAnimation;

void main() {

    fragment_mouse_data = mouse;
    fragment_texture_coord = vertex_texture_coord;
    fragment_window_size = windowSize;
    fragment_time_SpeedAnimation = time_SpeedAnimation;

    gl_Position = MVP * vec4(vertex_position, 0, 1);
}
