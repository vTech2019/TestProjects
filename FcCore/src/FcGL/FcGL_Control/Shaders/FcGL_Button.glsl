#version 110

varying vec4 fragment_windowWxWy_buttonWxWy;
varying vec4 fragment_mouse_data;
varying vec4 fragment_buttonXY_textureXY;
varying vec2 fragment_time_SpeedAnimation;

uniform sampler2D  controlID;

vec4 glButton(vec2 fragCoord, vec2 xy, vec2 widthHeight, vec4 color, vec2 mouse){
    vec2 m_xy = step(abs(fragCoord - xy), widthHeight);
    vec2 m_mouse_xy = step(abs(mouse.xy - xy), widthHeight);
    color = 0.5 * color + 0.5 * color * step(2.0, m_mouse_xy.x + m_mouse_xy.y);
    return  vec4(step(2.0, m_xy.x + m_xy.y)) * color;
}


void main() {
    float scale = 1.0 / min(fragment_window_size.x, fragment_window_size.y);
    vec2 xy = gl_FragCoord.xy * vec2(scale);
    vec2 mouse = fragment_mouse_data.xy * scale;   
    vec4 controlState = texture2D(controlID, fragment_buttonXY_textureXY.zw);
	gl_FragColor =  glButton(xy, fragment_buttonXY_textureXY.xy, fragment_windowWxWy_buttonWxWy.zw, controlState, mouse);
}
