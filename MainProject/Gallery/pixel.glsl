R"(

#version 430 compatibility

in vec2 texture_coord;
in flat uvec2 mouse_coord;

uniform sampler2D texture_0;

void main() {
    vec2 circle = vec2(mouse_coord - gl_FragCoord.xy);
    vec4 color = texture(texture_0, texture_coord);
    if(length(circle) < 10)
        gl_FragColor =  (vec4(vec3(1.0f, 1.0f, 1.0f) - color.xyz, 1.0));
    else{

        gl_FragColor =  texture(texture_0, texture_coord);
    }
}

)"