#version 430
in vec2 fragment_texture_coord;
in flat uvec2 fragment_mouse_coord;

uniform sampler2D  textureID;

out vec4 gl_FragColor;

void main() {
    vec2 circle = vec2(fragment_mouse_coord - gl_FragCoord.xy);
    if(length(circle) < 20)
    	gl_FragColor =  (vec4(vec3(1.0f, 1.0f, 1.0f), 1.0));
    else
    	gl_FragColor = texture2D(textureID, fragment_texture_coord);;
}
