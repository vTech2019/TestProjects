#version 110
#pragma debug(on)

varying vec2 fragment_window_size;
varying vec4 fragment_mouse_data;
varying vec2 fragment_texture_coord;
varying vec2 fragment_time_SpeedAnimation;

uniform sampler2D  textureID;
uniform sampler2D  controlID;

#define SWITCH_OFF 0.


vec4 glButton(vec2 fragCoord, vec2 xy, vec2 widthHeight, vec4 color, vec2 mouse){
    vec2 m_xy = step(abs(fragCoord - xy), widthHeight);
    vec2 m_mouse_xy = step(abs(mouse.xy - xy), widthHeight);
    color = 0.5 * color + 0.5 * color * step(2.0, m_mouse_xy.x + m_mouse_xy.y);
    return  vec4(step(2.0, m_xy.x + m_xy.y)) * color;
}
vec4 glSwitch(vec2 fragCoord, vec2 center, float radius, vec4 color, vec2 mouse, vec3 controlSwitch){
    color *= 0.333333;
    vec2 m_area = center - vec2(clamp(center.x - fragCoord.x, 0., 2. * radius), 0.);
    float m_area_length = distance(m_area, fragCoord);
    float ms = fract(fragment_time_SpeedAnimation.x);
    float switch_offset;
    if (controlSwitch.y == 1.0)
        switch_offset = 4. * (controlSwitch.z - 0.5);
    else
        switch_offset = 2. * abs(1. - ms - controlSwitch.x);
    vec2 m_switch = center - vec2(switch_offset * radius, 0.);
    float m_switch_length = distance(m_switch, fragCoord);
    float m_mouse_length = distance(m_switch, mouse.xy);
    vec3 m_step = step(vec3(m_switch_length, m_mouse_length, m_area_length), vec3(radius));
    vec4 m_color = color * m_step.x;
    m_color += color * m_step.y * m_step.x;
    m_color += color * m_step.z;
    return m_color;
}

void main() {
    float scale = 1.0 / min(fragment_window_size.x, fragment_window_size.y);
    vec2 xy = gl_FragCoord.xy * vec2(scale);
    vec2 mouse = fragment_mouse_data.xy * scale;   


    vec4 color = vec4(0.);
    bvec2 center = lessThan(gl_FragCoord.xy, fragment_window_size * 0.5);
    if (center.x && center.y){
        center = lessThan(gl_FragCoord.xy, fragment_window_size * 0.25);
        if (center.x && center.y){
            vec4 controlState = texture2D(controlID, vec2(0));
            //controlState.w = 1.;
            color += glButton(xy, vec2(0.08 + 0.04, 0.12 + 0.04), vec2(0.04, 0.02), vec4(0.25,0.25,1.0, 1.0), mouse);
            color += glSwitch(xy, vec2(0.08 + 0.04, 0.04 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);
            color += glSwitch(xy, vec2(0.08 + 0.12, 0.04 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);
            color += glSwitch(xy, vec2(0.08 + 0.20, 0.04 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);
            color += glSwitch(xy, vec2(0.08 + 0.28, 0.04 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);

            color += glSwitch(xy, vec2(0.08 + 0.04, 0.08 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);
            color += glSwitch(xy, vec2(0.08 + 0.12, 0.08 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);
            color += glSwitch(xy, vec2(0.08 + 0.20, 0.08 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);
            color += glSwitch(xy, vec2(0.08 + 0.28, 0.08 + 0.04), 0.02, vec4(0.25,0.25,1.00, 1.0), mouse, controlState.xyz);
        }
        
    }

    //color += glButton(xy, vec2(200, 200), vec2(20, 25), vec4(0.4,0.6,0.7, 1.), mouse);
    //color += glButton(xy, vec2(300, 300), vec2(80, 15), vec4(1.,1.,1., 1.0), mouse);
    //color += glButton(xy, vec2(400, 400), vec2(40, 15), vec4(1.,1.,1., 1.), mouse);
    //color += glButton(xy, vec2(500, 500), vec2(30, 15), vec4(1.,1.,1., 1.0), mouse);
    //if (length(circle) < 10.0)
	//    gl_FragColor =  vec4(smoothstep(circle.x, circle.y, 1.));
    //else
	gl_FragColor =  color;
    
}
