R"(
    #version 430

    in vec3 position;
    in vec2 vertex_texture_coord;
    in vec3 normal;

    uniform shader_data
    {
        mat4 viewMatrix;
        uvec4 mouseData;
    };

    out vec2 texture_coord;
    flat out uvec2 mouse_coord;

    void main(){
        mouse_coord = mouseData.xy;
        texture_coord = vec2(vertex_texture_coord.x, 1.0f - vertex_texture_coord.y);
        gl_Position = viewMatrix * vec4(position, 1.0f);
    }

)"